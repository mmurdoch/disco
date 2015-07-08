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
 * @param timeout_milliseconds the number of milliseconds to wait before
 * timing out when broadcasting messages
 * @return 0 on success, non-zero on failure
 */
int create_broadcast_socket(broadcast_socket_t* broadcast_socket, int port,
    size_t timeout_milliseconds);

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

/**
 * Receives a broadcasted message and null-terminates it.
 *
 * @param listener_socket the socket on which to receive the message
 * @param message_buffer the buffer into which to receive the message
 * @param message_buffer_size the maximum number of bytes to read into the
 * message buffer
 * @return number of bytes received or negative integer on error
 */
int receive_broadcast(listener_socket_t* listener_socket, char* message_buffer,
    size_t message_buffer_size);

#endif // DISCO_BROADCAST_H
