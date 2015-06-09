#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "broadcast.h"

int main() {
    int listening_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (listening_socket == -1) {
        print_error("Failed to create listening socket");
        exit(1);
    }

    int setsockopt_status;
    /* Setting SO_REUSEADDR is not needed on Mac OS X (any BSD?) to allow
       multiple copies of this program running on the same machine from
       receiving messages */
    /*int turn_on_address_reuse = 1;
    setsockopt_status = setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR,
        &turn_on_address_reuse, sizeof(turn_on_address_reuse));
    if (setsockopt_status == -1) {
        print_error("Failed to turn on address reuse");
        exit(1);
    }*/

    /* Setting SO_REUSEPORT is needed on Mac OS X (any BSD?) to allow multiple
       copies of this program running on the same machine from reeiving messages
       Windows systems do not recognize this setting. What about Linux? What
       about Solaris? */
    int turn_on_port_reuse = 1;
    setsockopt_status = setsockopt(listening_socket, SOL_SOCKET, SO_REUSEPORT,
        &turn_on_port_reuse, sizeof(turn_on_port_reuse));
    if (setsockopt_status == -1) {
        print_error("Failed to turn on port reuse");
        exit(1);
    }

    struct sockaddr_in listener_address;
    socklen_t address_length = sizeof(listener_address);
    int listener_port = 54545;

    memset(&listener_address, 0, sizeof(listener_address));
    listener_address.sin_family = AF_INET;
    listener_address.sin_addr.s_addr = INADDR_ANY;
    listener_address.sin_port = htons(listener_port);

    printf("Listening for broadcasts...\n");

    size_t buffer_length = 8;
    char buffer[buffer_length];

    while (1) {
        ssize_t received_bytes_count = recvfrom(listening_socket, &buffer, 
            buffer_length, 0, (struct sockaddr*) &listener_address, 
            &address_length);

        printf("Received \"%s\" from \n", buffer);
    }

    int close_status = close(listening_socket);
    if (close_status == -1) {
        print_error("Failed to close listening socket");
        exit(1);
    }

    return 0;
}
