import requests
import json
import sqlite3
from datetime import datetime
import time
import re
import os
import logging
import tldextract
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
import signal
import sys
from threading import Thread
import queue

# Configuração inicial de logging
logging.getLogger("urllib3").setLevel(logging.WARNING)
logging.getLogger("requests").setLevel(logging.WARNING)

# Configurações
DEBUG = False
MAX_PAGES = 5
MAX_CYCLES_WITHOUT_NEW = 50000
H1_PUBLIC_QUERY_URL = "https://hackerone.com/programs/search?query=type:hackerone&sort=published_at:descending&page={page}"

# BLACKLIST de domínios para excluir
DOMAIN_BLACKLIST = [
    "github.com",
    "*.github.com",
    "github.io",
    "*.github.io",
    "gitlab.com",
    "*.gitlab.com",
    "bitbucket.org",
    "*.bitbucket.org",
    "azurewebsites.net",
    "*.azurewebsites.net",
    "cloudapp.net",
    "*.cloudapp.net",
    "amazonaws.com",
    "*.amazonaws.com",
    "herokuapp.com",
    "*.herokuapp.com",
    "firebaseapp.com",
    "*.firebaseapp.com",
    "web.app",
    "*.web.app",
    "*.android",
    "googleapis.com",
    "*.googleapis.com"
]

# Configuração de padrões regex para URLs indesejadas
URL_BLACKLIST_PATTERNS = [
    r"^https?://([a-z0-9-]+\.)*github\.com/",
    r"^https?://([a-z0-9-]+\.)*gitlab\.com/",
    r"^https?://([a-z0-9-]+\.)*bitbucket\.org/",
    r"^https?://([a-z0-9-]+\.)*azurewebsites\.net/",
    r"^https?://([a-z0-9-]+\.)*cloudapp\.net/",
    r"^https?://([a-z0-9-]+\.)*amazonaws\.com/",
    r"^https?://([a-z0-9-]+\.)*herokuapp\.com/",
    r"^https?://([a-z0-9-]+\.)*firebaseapp\.com/",
    r"^https?://([a-z0-9-]+\.)*web\.app/"
]

# GraphQL Queries
POLICY_SCOPE_QUERY = """
query PolicySearchStructuredScopesQuery($handle: String!) {
  team(handle: $handle) {
    structured_scopes_search {
      nodes {
        ... on StructuredScopeDocument {
          identifier
          eligible_for_bounty
          eligible_for_submission
          display_name
          instruction
        }
      }
    }
  }
}
"""

SCOPE_QUERY = """
query TeamAssets($handle: String!) {
  team(handle: $handle) {
    in_scope_assets: structured_scopes(
      archived: false
      eligible_for_submission: true
    ) {
      edges {
        node {
          asset_identifier
          asset_type
          eligible_for_bounty
        }
      }
    }
  }
}
"""

BASE_DIR = "/home/eliane/BugBounty/subdomains"
DB_FILE = os.path.join(BASE_DIR, "subdomains.db")
RATE_LIMIT = 600
REQUEST_COUNT = 0
LAST_RESET_TIME = time.time()

EXCLUDE_KEYWORDS = []

logging.basicConfig(
    filename=os.path.join(BASE_DIR, 'scanner.log'),
    level=logging.DEBUG if DEBUG else logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

stop_queue = queue.Queue()

def check_stop_command():
    """Monitora entrada do usuário para comando de parada"""
    while True:
        cmd = input().strip().lower()
        if cmd == "pare":
            stop_queue.put(True)
            break
        time.sleep(0.1)

def check_rate_limit():
    global REQUEST_COUNT, LAST_RESET_TIME
    current_time = time.time()
    if current_time - LAST_RESET_TIME >= 60:
        REQUEST_COUNT = 0
        LAST_RESET_TIME = current_time
    if REQUEST_COUNT >= RATE_LIMIT:
        sleep_time = 60 - (current_time - LAST_RESET_TIME)
        print(f"Limite de taxa atingido. Pausando por {sleep_time:.1f}s...")
        time.sleep(sleep_time)
        REQUEST_COUNT = 0
        LAST_RESET_TIME = time.time()
    REQUEST_COUNT += 1

def init_db():
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS subdomains 
                 (domain TEXT, handle TEXT, date_added TEXT, 
                  bounty_eligible INTEGER, platform TEXT, 
                  program_name TEXT, checked INTEGER DEFAULT 0, 
                  PRIMARY KEY (domain, handle))''')
    conn.commit()
    conn.close()

def is_blacklisted_domain(domain):
    """
    Verifica se o domínio está na blacklist
    """
    if not domain:
        return True
        
    domain_lower = domain.lower()
    
    # Verifica contra a blacklist de domínios
    for blacklisted_domain in DOMAIN_BLACKLIST:
        if blacklisted_domain.startswith('*.'):
            # Padrão wildcard como *.github.com
            base_domain = blacklisted_domain[2:]
            if domain_lower.endswith('.' + base_domain) or domain_lower == base_domain:
                return True
        else:
            # Domínio exato
            if domain_lower == blacklisted_domain:
                return True
    
    # Verifica contra padrões regex de URLs
    for pattern in URL_BLACKLIST_PATTERNS:
        if re.search(pattern, domain_lower):
            return True
    
    return False

def sanitize_domain(domain):
    extracted = tldextract.extract(domain)
    if not extracted.suffix:
        return ""
    return f"{extracted.subdomain}.{extracted.domain}.{extracted.suffix}".strip('.').lower()

def smart_filter(domain):
    domain = sanitize_domain(domain)
    if not domain:
        return False
    
    # Verifica se o domínio está na blacklist
    if is_blacklisted_domain(domain):
        return False
    
    tld = domain.split('.')[-1]
    if len(tld) < 2 or not tld.isalpha():
        return False
    
    if not re.match(r'^([a-z0-9-]+\.)*[a-z0-9-]+\.[a-z]{2,}$', domain):
        return False
    
    if any(kw in domain for kw in EXCLUDE_KEYWORDS):
        return False
    
    return domain

def save_subdomains(subdomains, handle, program_name):
    conn = sqlite3.connect(DB_FILE)
    c = conn.cursor()
    current_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    new_domains = []
    
    for raw_domain, eligible_sub, eligible_bounty in subdomains:
        domain = smart_filter(raw_domain)
        if not domain:
            continue
        
        try:
            c.execute('''INSERT OR IGNORE INTO subdomains 
                      (domain, handle, program_name, date_added, 
                       bounty_eligible, platform) 
                      VALUES (?, ?, ?, ?, ?, ?)''',
                    (domain, handle, program_name, current_date,
                     1 if eligible_bounty else 0, "HackerOne"))
            if c.rowcount > 0:
                new_domains.append(domain)
        except sqlite3.IntegrityError:
            continue
    
    conn.commit()
    conn.close()
    return new_domains

def setup_session():
    session = requests.Session()
    retry = Retry(
        total=3,
        backoff_factor=1,
        status_forcelist=[429, 500, 502, 503, 504]
    )
    adapter = HTTPAdapter(max_retries=retry)
    session.mount('https://', adapter)
    session.headers.update({
        'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36',
        'Accept': 'application/json'
    })
    return session

def fetch_page(session, page):
    try:
        check_rate_limit()
        response = session.get(H1_PUBLIC_QUERY_URL.format(page=page), timeout=30)
        if response.status_code != 200:
            return None
        return json.loads(response.text).get("results", [])
    except Exception as e:
        logging.error(f"Erro na página {page}: {str(e)}")
        return None

def process_program(session, program):
    handle = program["handle"]
    program_name = program.get("name", handle)
    domains = []
    
    # Primeira query
    payload = json.dumps({
        "query": POLICY_SCOPE_QUERY,
        "variables": {"handle": handle}
    })
    check_rate_limit()
    scope_resp = session.post("https://hackerone.com/graphql", 
                            data=payload, 
                            headers={"Content-Type": "application/json"})
    
    if scope_resp.status_code == 200:
        nodes = scope_resp.json().get("data", {}).get("team", {}).get("structured_scopes_search", {}).get("nodes", [])
        for node in nodes:
            if node.get("eligible_for_submission"):
                identifier = node.get("identifier", "")
                if identifier:
                    # Filtra URLs indesejadas antes de processar
                    filtered_ids = []
                    for id in identifier.split(','):
                        id_clean = id.strip()
                        if not is_blacklisted_domain(id_clean):
                            filtered_ids.append(id_clean)
                    
                    if filtered_ids:
                        domains.extend([(id, node["eligible_for_submission"], node["eligible_for_bounty"]) for id in filtered_ids])
    
    # Segunda query
    payload = json.dumps({
        "query": SCOPE_QUERY,
        "variables": {"handle": handle}
    })
    check_rate_limit()
    scope_resp = session.post("https://hackerone.com/graphql", 
                            data=payload, 
                            headers={"Content-Type": "application/json"})
    
    if scope_resp.status_code == 200:
        edges = scope_resp.json().get("data", {}).get("team", {}).get("in_scope_assets", {}).get("edges", [])
        for edge in edges:
            node = edge.get("node", {})
            identifier = node.get("asset_identifier", "")
            if identifier and node.get("asset_type") in ["Domain", "URL"]:
                # Filtra URLs indesejadas antes de processar
                filtered_ids = []
                for id in identifier.split(','):
                    id_clean = id.strip()
                    if not is_blacklisted_domain(id_clean):
                        filtered_ids.append(id_clean)
                
                if filtered_ids:
                    domains.extend([(id, True, node["eligible_for_bounty"]) for id in filtered_ids])
    
    return (handle, program_name, domains)

def main_loop():
    init_db()
    session = setup_session()
    cycles_without_new = 0
    page = 1
    
    while cycles_without_new < MAX_CYCLES_WITHOUT_NEW and not stop_queue.qsize():
        total_new = 0
        for current_page in range(1, MAX_PAGES + 1):
            programs = fetch_page(session, current_page)
            if not programs:
                break
            
            page_new = 0
            for program in programs:
                handle, program_name, domains = process_program(session, program)
                new_domains = save_subdomains(domains, handle, program_name)
                page_new += len(new_domains)
            
            print(f"Página {current_page} processada. Novos domínios: {page_new}")
            total_new += page_new
            time.sleep(5)
        
        if total_new == 0:
            cycles_without_new += 1
            print(f"Ciclo completo sem novos domínios ({cycles_without_new}/{MAX_CYCLES_WITHOUT_NEW})")
        else:
            cycles_without_new = 0
        
        time.sleep(60)
    
    print("Nenhum novo domínio encontrado após vários ciclos. Encerrando...")

def signal_handler(sig, frame):
    print("\nFinalizando graciosamente...")
    stop_queue.put(True)
    sys.exit(0)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)
    Thread(target=check_stop_command, daemon=True).start()
    main_loop()
