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
 * @param broadcast_socket on success populated with the created socket
 * @param port the port to which to broadcast
 * @return 0 on success, non-zero on failure
 */
int create_broadcast_socket(broadcast_socket_t* broadcast_socket, int port);

/**
 * Destroys a socket created via create_broadcast_socket.
 *
 * @param broadcast_socket the socket to destroy
 */
void destroy_broadcast_socket(broadcast_socket_t* broadcast_socket);

/**
 * Broadcasts a message.
 *
 * @param broadcast_socket the socket on which to broadcast the message
 * @param message the message to broadcast
 * @return number of bytes broadcasted or negative integer on error
 */
int broadcast_message(broadcast_socket_t* broadcast_socket, const char* message);

/**
 * Creates a socket for listening to broadcast messages.
 *
 * @param listener_socket on success populated with the created socket
 * @param port the port on which to listening
 * @param timeout_milliseconds the number of milliseconds to wait before
 * timing out when listening for messages
 * @return 0 on success, non-zero on failure
 */
int create_listener_socket(listener_socket_t* listener_socket, int port,
    size_t timeout_milliseconds);

/**
 * Destroys a socket created via create_listener_socket.
 *
 * @param listener_socket the socket to destroy
 */
void destroy_listener_socket(listener_socket_t* listener_socket);

#endif // DISCO_BROADCAST_H
