#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "broadcast.h"

int main() {
    int broadcasting_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (broadcasting_socket == -1) {
        print_error("Failed to create broadcasting socket");
        exit(1);
    }

    int turn_on_broadcasting = 1;
    int setsockopt_status = setsockopt(broadcasting_socket, SOL_SOCKET, SO_BROADCAST,
        &turn_on_broadcasting, sizeof(turn_on_broadcasting));
    if (setsockopt_status == -1) {
        print_error("Failed to turn on broadcasting on");
        exit(1);
    }

    struct sockaddr_in broadcast_address;
    int broadcast_port = 54545;

    memset(&broadcast_address, 0, sizeof(broadcast_address));
    broadcast_address.sin_family = AF_INET;
    broadcast_address.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_address.sin_port = htons(broadcast_port);

    ssize_t sent_bytes_count = sendto(broadcasting_socket, "", 0, 0,
        (struct sockaddr*) &broadcast_address, sizeof(broadcast_address));
    if (sent_bytes_count == -1) {
        print_error("Failed to send broadcast message");
        exit(1);
    }

    int close_status = close(broadcasting_socket);
    if (close_status == -1) {
        print_error("Failed to close broadcast socket");
        exit(1);
    }

    return 0;
}
