from __future__ import print_function
import socket

try:
    listening_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

    listener_address = ('', 54545)
    listening_socket.bind(listener_address)
    print('Listening for broadcasts...')

    while True:
        received_data, from_address = listening_socket.recvfrom(2048)
        print('Received "' + received_data + '" from ' + str(from_address))
except KeyboardInterrupt:
    pass
