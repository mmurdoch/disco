from __future__ import print_function
import socket

try:
    address = ('', 54545)
    listening_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    listening_socket.bind(address)
    print('Listening for broadcasts...')
    while True:
        recv_data, addr = listening_socket.recvfrom(2048)
        print('Received "' + recv_data + '" from ' + str(addr))
        #listening_socket.sendto("*" + recv_data, addr)
except KeyboardInterrupt:
    pass
