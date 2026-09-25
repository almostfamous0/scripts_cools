#!/usr/bin/env python3

from requests import head

headers_to_check = [
    'Content-Security-Policy',
    'Strict-Transport-Security',
    'X-Frame-Options',
    'X-XSS-Protection',
    'X-Content-Type-Options',
    'Referrer-Policy',
    'Feature-policy'
]

def check_security(url):
    missing_headers = []
    res = head(url)

    for header in headers_to_check:
        if header not in res.headers:
            missing_headers.append(header)

    if len(missing_headers) == 0:
        print(f'[+] {url} site OK !')
    else:
        print(f'[-] {url} faltam os headers:')
        for x in missing_headers:
            print(x)

    print(res.headers)

check_security('https://' + input('[+] URL: '))
