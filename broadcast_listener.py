import socket
address = ('', 54545)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
server_socket.bind(address)

while True:
    print "Listening"
    recv_data, addr = server_socket.recvfrom(2048)
    print addr,':',recv_data
    server_socket.sendto("*"+recv_data, addr)