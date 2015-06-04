import socket

address = ('<broadcast>', 54545)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

to_send = ""
client_socket.sendto(to_send, address)
received, server_address = client_socket.recvfrom(2048)
print server_address[0]