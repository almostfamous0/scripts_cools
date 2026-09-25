import sys
from scapy.all import ARP, Ether, srp
from manuf import manuf

def get_vendor(mac_address):
    try:
        return manuf.MacParser().get_manuf(mac_address)
    except manuf.ManufLookupError:
        return "Desconhecido"

def scan_local_network(ip_range, interface):
    arp = ARP(pdst=ip_range)
    ether = Ether(dst='ff:ff:ff:ff:ff:ff')
    packet = ether/arp
    result = srp(packet, timeout=3, iface=interface, verbose=0)[0]
    devices = []

    for sent, received in result:
        mac_address = received.hwsrc
        vendor = get_vendor(mac_address)
        devices.append({'ip': received.psrc, 'mac': mac_address, 'vendor': vendor})
    return devices

if len(sys.argv) != 3:
    print("Uso: python3 script.py <intervalo IP> <placa>")
    print("Ex: python3 script.py 192.168.1.1/24 eth0")
    sys.exit(1)

ip_range = sys.argv[1]
interface = sys.argv[2]
devices = scan_local_network(ip_range, interface)

if devices:
    print('Dispositivos:')
    print('----')
    for device in devices:
        print(f'IP: {device["ip"]}, MAC: {device["mac"]}, Fabricante: {device["vendor"]}')
else:
    print('Nenhum encontrado.')

