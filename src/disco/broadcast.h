#ifndef DISCO_BROADCAST_H
#define DISCO_BROADCAST_H

#include "udp.h"

/**
 * Creates a socket for broadcasting messages.
 *
 * @param port the port to which to broadcast
 * @param broadcast_socket on success populated with the created socket
 * @return 0 on success, non-zero on failure
 */
int create_broadcast_socket(udp_socket_t* broadcast_socket, int port);

/**
 * Destroys a socket created via create_broadcast_socket.
 *
 * @param broadcast_socket the socket to destroy
 */
void destroy_broadcast_socket(udp_socket_t* broadcast_socket);

int broadcast_message(udp_socket_t broadcast_socket, const char* message);

int create_broadcast_listener_socket(udp_socket_t* listener_socket, int port,
    size_t timeout_milliseconds);

void destroy_broadcast_listener_socket(udp_socket_t* listener_socket);

#endif // DISCO_BROADCAST_H
