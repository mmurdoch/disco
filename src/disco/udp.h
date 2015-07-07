#ifndef DISCO_UDP_H
#define DISCO_UDP_H

#include <netdb.h>

typedef struct _udp_socket_t* udp_socket_t;

/**
 * Creates a UDP socket.
 *
 * @param the_socket on success populated with the created socket
 * @param ip_address the IP address which the socket can send data to or NULL
 * to bind to and receive data on the first available IP address
 * @param port the port to connect to
 * @return 0 on success non-zero on failure
 */
int create_udp_socket(udp_socket_t* the_socket, const char* ip_address,
    int port);

/**
 * Destroys a UDP socket created via create_udp_socket.
 *
 * @param the_socket the socket to destroy
 */
void destroy_udp_socket(udp_socket_t* the_socket);

/**
 * Turns on a UDP socket option.
 *
 * @param socket the socket for which to turn on the option
 * @param option_name the name of the option to turn on
 * @return 0 on success, -1 on failure
 */
int turn_on_socket_option(udp_socket_t socket, int option_name);

/**
 * Sets the timeout for receiving data from a UDP socket.
 *
 * @param socket the socket for which to set the timeout
 * @param milliseconds the timeout duration in milliseconds
 * @return 0 on success, -1 on failure
 */
int set_receive_timeout(udp_socket_t socket, size_t milliseconds);

/**
 * Binds a UDP socket to its address so that it can receive messages.
 *
 * @param socket the socket for which to bind to its address
 * @return 0 on success, -1 on failure
 */
int bind_to_address(udp_socket_t socket);

/**
 * Retrieves the underlying socket handle for a socket.
 *
 * @param socket the socket for which to retrieve the underlying handle
 * @return the underlying socket handle
 */
int get_socket_handle(udp_socket_t socket);

/**
 * Retrieves the IP address to which a socket is connected.
 *
 * @param socket the socket for which to retrieve the IP address
 * @return the IP address of the socket
 */
struct sockaddr* get_address(udp_socket_t socket);

/**
 * Retrieves the length (sizeof) the IP address to which a socket is connected.
 *
 * @param socket the socket for which to retrieve the address length
 * @return the length of the IP address of the socket
 */
socklen_t get_address_length(udp_socket_t socket);

/**
 * Retrieves the port to which a socket is connected.
 *
 * @param socket the socket for which to retrieve the port
 * @return the port number
 */
int get_port(udp_socket_t socket);

/**
 * Sends a message via a socket.
 *
 * @param socket the socket on which to send the message
 * @param message the null-terminated message to send (the null terminator is
 * not sent)
 * @return number of bytes sent or -1 on error
 */
int send_message(udp_socket_t socket, const char* message);

/**
 * Receives a message from a socket.
 *
 * @param socket the socket from which to receive the message
 * @param message the buffer into which to write the message
 * @param max_message_length the maximum number of bytes to read into the
 * message buffer
 * @return the number of bytes written to the message buffer or -1 on error
 */
int receive_message(udp_socket_t socket, char* message,
    size_t max_message_length);

#endif // DISCO_UDP_H
