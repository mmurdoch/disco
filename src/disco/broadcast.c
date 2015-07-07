#include "broadcast.h"

#include "udp.h"

/**
 * Creates a socket for broadcasting messages.
 *
 * @param port the port to which to broadcast
 * @param broadcast_socket on success populated with the created socket
 * @return 0 on success, non-zero on failure
 */
int create_broadcast_socket(udp_socket_t* broadcast_socket, int port) {
    char* broadcast_ip = "255.255.255.255";

    if (create_udp_socket(broadcast_socket, broadcast_ip, port) != 0) {
        return -1;
    }

    if (turn_on_socket_option(*broadcast_socket, SO_BROADCAST) != 0) {
        destroy_broadcast_socket(broadcast_socket);
        return -1;
    }

    return 0;
}

/**
 * Destroys a socket created via create_broadcast_socket.
 *
 * @param broadcast_socket the socket to destroy
 */
void destroy_broadcast_socket(udp_socket_t* broadcast_socket) {
    destroy_udp_socket(broadcast_socket);
}

int broadcast_message(udp_socket_t broadcast_socket, const char* message) {
    return send_message(broadcast_socket, message);
}
