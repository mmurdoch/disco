from __future__ import print_function
import socket

address = ('<broadcast>', 54545)
broadcasting_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
broadcasting_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

to_send = ""
broadcasting_socket.sendto(to_send, address)
#received, receiver_address = broadcasting_socket.recvfrom(2048)
#print("Receiver address: " + receiver_address[0])
