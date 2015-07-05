from __future__ import print_function
import socket

try:
    listening_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Setting SO_REUSEADDR is not needed on Mac OS X (any BSD?) to allow
    # multiple copies of this program running on the same machine from
    # receiving messages
    #listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    # Setting SO_REUSEPORT is needed on Mac OS X (any BSD?) to allow multiple
    # copies of this program running on the same machine from receiving messages
    # Windows systems do not recognize this setting. What about Linux? What
    # about Solaris?
    listening_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

    listener_address = ('', 54545)
    listening_socket.bind(listener_address)
    print('Listening for broadcasts...')

    while True:
        received_data, from_address = listening_socket.recvfrom(2048)
        print('Received "' + received_data + '" from ' + str(from_address))
except KeyboardInterrupt:
    pass
