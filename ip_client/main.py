#!/usr/bin/env python3
import threading
from socket import AF_INET, SOCK_DGRAM, socket

from config import SERVER_ADDRESS, SERVER_PORT
from definitions import AnsiColors
from utility import print_protected


def main():
    print(f"TCP/IP client for the STM32 lwIP RTEMS example")
    sender = threading.Thread(target=sender_thread, args=(None,))
    listener = threading.Thread(target=listener_thread, args=(None,))
    sender.start()
    listener.start()
    sender.join()
    listener.join()
    print(f"{AnsiColors.RESET}Finished")


def sender_thread(args: any):
    from config import TCPIP_PROT
    from definitions import Protocols

    if TCPIP_PROT == Protocols.TCPIP_PROT_0_TCP:
        tcp_sender()
    elif TCPIP_PROT == Protocols.TCPIP_PROT_1_UDP:
        udp_sender()
    pass


def tcp_sender():
    pass


def udp_sender():
    server_socket = socket(AF_INET, SOCK_DGRAM)
    target_address = SERVER_ADDRESS, SERVER_PORT
    string = "Hello, this is a UDP test!"
    data = string.encode(encoding='utf-8')
    print_protected(f"Test string to be sent: {string}")
    bytes_sent = server_socket.sendto(data, target_address)
    print_protected(f"{AnsiColors.CYAN}Sender: Sent {bytes_sent} bytes to server")


def listener_thread(args: any):
    pass


if __name__ == "__main__":
    main()

