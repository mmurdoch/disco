#include "broadcast.h"

#include <stdlib.h>
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

int create_broadcast_listener_socket(udp_socket_t* listener_socket, int port,
    size_t timeout_milliseconds) {

    if (create_udp_socket(listener_socket, NULL, port) != 0) {
        return -1;
    }

    /* Setting SO_REUSEADDR is not needed on Mac OS X (any BSD?) to allow
       multiple copies of this program running on the same machine from
       receiving messages. It is probably needed on Windows. */
    /*if (turn_on_socket_option(listener_socket, SO_REUSEADDR) == -1) {
        destroy_udp_socket(listener_socket);
        return -1;
    }*/

    /* Setting SO_REUSEPORT is needed on Mac OS X (any BSD?) to allow multiple
       copies of this program running on the same machine from receiving messages.
       Windows systems do not recognize this setting. What about Linux? What
       about Solaris? */
    if (turn_on_socket_option(*listener_socket, SO_REUSEPORT) != 0) {
        destroy_broadcast_listener_socket(listener_socket);
        return -1;
    }

    if (bind_to_address(*listener_socket) != 0) {
        destroy_broadcast_listener_socket(listener_socket);
        return -1;
    }

    if (set_receive_timeout(*listener_socket, timeout_milliseconds) != 0) {
        destroy_broadcast_listener_socket(listener_socket);
        return -1;
    }

    return 0;
}

void destroy_broadcast_listener_socket(udp_socket_t* listener_socket) {
    destroy_udp_socket(listener_socket);
}
