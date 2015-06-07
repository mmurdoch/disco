#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>

#include "broadcast.h"

int main() {
    int listening_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (listening_socket == -1) {
        print_error("Failed to create listening socket");
        exit(1);
    }

    int turn_on_address_reuse = 1;
    int setsockopt_status = setsockopt(listening_socket, SOL_SOCKET, SO_BROADCAST,
        &turn_on_address_reuse, sizeof(turn_on_address_reuse));
    /* TODO */

    int close_status = close(listening_socket);
    if (close_status == -1) {
        print_error("Failed to close listening socket");
        exit(1);
    }

    return 0;
}
