#ifndef DISCO_BROADCAST_H
#define DISCO_BROADCAST_H

#include <stdlib.h>
#include "udp.h"

typedef struct {
    udp_socket_t udp_socket;
} broadcast_socket_t;

typedef struct {
    udp_socket_t udp_socket;
} listener_socket_t;

/**
 * Creates a socket for broadcasting messages.
 *
 * @param port the port to which to broadcast
 * @param broadcast_socket on success populated with the created socket
 * @return 0 on success, non-zero on failure
 */
int create_broadcast_socket(broadcast_socket_t* broadcast_socket, int port);

/**
 * Destroys a socket created via create_broadcast_socket.
 *
 * @param broadcast_socket the socket to destroy
 */
void destroy_broadcast_socket(broadcast_socket_t* broadcast_socket);

int broadcast_message(broadcast_socket_t* broadcast_socket, const char* message);

int create_listener_socket(listener_socket_t* listener_socket, int port,
    size_t timeout_milliseconds);

void destroy_listener_socket(listener_socket_t* listener_socket);

#endif // DISCO_BROADCAST_H
