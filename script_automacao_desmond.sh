#!/bin/bash

# ANSI color codes
RED='\033[91m'
RESET='\033[0m'

# ASCII art
echo -e "${RED}"
cat << "EOF"
   _____                                      _
 |  __ \                                    | |
 | |  | | ___  ___ _ __ ___   ___  _ __   __| |
 | |  | |/ _ \/ __| '_ ` _ \ / _ \| '_ \ / _` |
 | |__| |  __/\__ \ | | | | | (_) | | | | (_| |
 |_____/ \___||___/_| |_| |_|\___/|_| |_|\__,_|

                                                v1.0.0

                               Made by D3smond (desmondelite)
EOF
echo -e "${RESET}"

# Telegram Notification Function
send_telegram() {
    local message=$1
    local bot_token="6191942150:AAHUk0jlu-4l73ffmzD3EKunqhEjC-YlRqs"
    local chat_id="184541223"
    local url="https://api.telegram.org/bot$bot_token/sendMessage"

    if [[ -n $message ]]; then
        local payload=$(jq -nc --arg text "$message" --arg chat_id "$chat_id" '{chat_id: $chat_id, text: $text}')
        curl -s -X POST $url -H "Content-Type: application/json" -d "$payload"
    fi
}

# Help menu
display_help() {
    echo -e "NucleiFuzzer is a Powerful Automation tool for detecting XSS, SQLi, SSRF, Open-Redirect, etc. vulnerabilities in Web Applications\n\n"
    echo -e "Usage: $0 [options]\n\n"
    echo "Options:"
    echo "  -h, --help              Display help information"
    echo "  -d, --domain <domain>   Single domain to scan for vulnerabilities"
    echo "  -f, --file <filename>   File containing multiple domains/URLs to scan"
    exit 0
}



# Get the current user's home directory
home_dir=$(eval echo ~"$USER")

excluded_extentions="png,jpg,gif,jpeg,swf,woff,svg,pdf,json,css,js,webp,woff2,eot,ttf,otf,mp4,txt"

# Check and install dependencies
install_dependencies() {
    if [ ! -d "$home_dir/ParamSpider" ]; then
        echo "Cloning ParamSpider..."
        git clone https://github.com/0xKayala/ParamSpider "$home_dir/ParamSpider"
    fi

    if [ ! -d "$home_dir/fuzzing-templates" ]; then
        echo "Cloning fuzzing-templates..."
        git clone https://github.com/0xKayala/fuzzing-templates.git "$home_dir/fuzzing-templates"
    fi

    if ! command -v nuclei &> /dev/null; then
        echo "Installing Nuclei..."
        go install -v github.com/projectdiscovery/nuclei/v3/cmd/nuclei@latest
    fi

    if ! command -v httpx &> /dev/null; then
        echo "Installing httpx..."
        go install -v github.com/projectdiscovery/httpx/cmd/httpx@latest
    fi
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -h|--help)
            display_help
            ;;
        -d|--domain)
            domain="$2"
            shift; shift
            ;;
        -f|--file)
            filename="$2"
            shift; shift
            ;;
        *)
            echo "Unknown option: $key"
            display_help
            ;;
    esac
done

# Check for required inputs
if [ -z "$domain" ] && [ -z "$filename" ]; then
    echo "Please provide a domain with -d or a file with -f option."
    display_help
fi

# Install dependencies
install_dependencies

# Define output directory
output_dir="output"
mkdir -p "$output_dir"
output_file="$output_dir/allurls.txt"

# Function to run ParamSpider and collect URLs
run_paramspider() {
    local target_domain=$1
    local output_file=$2
    python3 "$home_dir/ParamSpider/paramspider.py" -d "$target_domain" --exclude "$excluded_extentions" --level high --quiet -o "$output_file"
}

# Process input
if [ -n "$domain" ]; then
    echo "Running ParamSpider on $domain"
    run_paramspider "$domain" "$output_dir/$domain.txt"
elif [ -n "$filename" ]; then
    echo "Running ParamSpider on URLs from $filename"
    while IFS= read -r line; do
        run_paramspider "$line" "$output_dir/$line.txt"
        cat "$output_dir/$line.txt" >> "$output_file"  # Append to the combined output file
    done < "$filename"
fi

# Check whether URLs were collected
if [ ! -s "$output_dir/$domain.txt" ] && [ ! -s "$output_file" ]; then
    echo "No URLs Found. Exiting..."
    exit 1
fi

# Function to run Nuclei
run_nuclei() {
    local input_file=$1
    sort "$input_file" | uniq | httpx -silent -mc 200,301,302 | nuclei -t "$home_dir/fuzzing-templates" -rl 05
}


process_nuclei_output() {
    local output=$1
    local formatted_message=""

    # Verificar cada linha para encontrar falhas
    while IFS= read -r line; do
        if [[ $line =~ \[(.*?)\]\ \[(.*?)\]\ \[(.*?)\]\ (http.*) ]]; then
            local vulnerability="${BASH_REMATCH[1]}"
            local protocol="${BASH_REMATCH[2]}"
            local severity="${BASH_REMATCH[3]}"
            local url="${BASH_REMATCH[4]}"

            formatted_message+="Vulnerability: $vulnerability, Protocol: $protocol, Severity: $severity, URL: $url\n"
        fi
    done <<< "$output"

    if [ -n "$formatted_message" ]; then
        send_telegram "$formatted_message"
    fi
}

# Função para processar a saída do Nuclei e enviar notificações via Telegram
process_and_notify() {
    local input_file=$1
    while IFS= read -r line; do
        echo "$line"  # Mostra a linha em tempo real
        # Remove os códigos ANSI
        local cleaned_line=$(echo "$line" | sed 's/\x1b\[[0-9;]*m//g')
        if [[ $cleaned_line =~ \[(.*?)\]\ \[(.*?)\]\ \[(.*?)\]\ (http.*) ]]; then
            local formatted_message="Vulnerability: ${BASH_REMATCH[1]}, Protocol: ${BASH_REMATCH[2]}, Severity: ${BASH_REMATCH[3]}, URL: ${BASH_REMATCH[4]}"
            send_telegram "$formatted_message"
        fi
    done < <(sort "$input_file" | uniq | httpx -silent -mc 200,301,302 | nuclei -t "$home_dir/fuzzing-templates" -rl 05)
}


# Execução do Nuclei com processamento em tempo real e notificação
echo "Running Nuclei on collected URLs"
if [ -n "$domain" ]; then
    process_and_notify "$output_dir/$domain.txt"
elif [ -n "$filename" ]; then
    process_and_notify "$output_file"
fi

echo "Scan is completed - Happy Fuzzing"
