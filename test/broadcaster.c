#include <stdio.h>
#include <stdlib.h>

#include <disco/broadcast.h>

int main(int argc, char *argv[]) {
    broadcast_socket_t broadcast_socket;
    int port = 4950;

    if (create_broadcast_socket(&broadcast_socket, port) != 0) {
        fprintf(stderr, "Failed to create broadcasting socket\n");
        exit(1);
    }

    if (broadcast_message(&broadcast_socket, "DSC10HERE") != 0) {
        fprintf(stderr, "Failed to send broadcast message\n");
        destroy_broadcast_socket(&broadcast_socket);
        exit(1);
    }

    destroy_broadcast_socket(&broadcast_socket);

    return 0;
}
