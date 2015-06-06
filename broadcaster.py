from __future__ import print_function
import socket

broadcasting_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
broadcasting_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

address = ('<broadcast>', 54545)
broadcasting_socket.sendto('', address)
