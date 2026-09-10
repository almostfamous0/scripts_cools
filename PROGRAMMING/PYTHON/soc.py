#!/usr/bin/env python3
from socket import socket, AF_INET, SOCK_STREAM

def recvall(sock):
    # Helper function to recv n bytes or return None if EOF is hit
    data = bytearray()

    while len(data) < 100:
        packet = sock.recv(len(data))
        if not packet:
            return None
        data.extend(packet)
    return data


with socket(AF_INET, SOCK_STREAM) as sock:
    sock.connect(("192.168.0.1", 80))
    sock.send(b'GET / HTTP/1.1\r\nHost: 192.168.0.1\r\n\r\n')
    r = recvall(sock)
    print(r.decode('utf-8'))
