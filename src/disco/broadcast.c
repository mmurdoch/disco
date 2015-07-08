#include "broadcast.h"

#include <stdlib.h>
#include "udp.h"

int create_broadcast_socket(broadcast_socket_t* broadcast_socket, int port,
    size_t timeout_milliseconds) {
    char* broadcast_ip = "255.255.255.255";

    udp_socket_t* udp_socket = &(broadcast_socket->udp_socket);

    if (create_udp_socket(udp_socket, broadcast_ip, port) != 0) {
        return -1;
    }

    if (turn_on_socket_option(udp_socket, SO_BROADCAST) != 0) {
        destroy_broadcast_socket(broadcast_socket);
        return -1;
    }

    if (set_send_timeout(udp_socket, timeout_milliseconds) != 0) {
        destroy_broadcast_socket(broadcast_socket);
        return -1;
    }

    return 0;
}

void destroy_broadcast_socket(broadcast_socket_t* broadcast_socket) {
    destroy_udp_socket(&(broadcast_socket->udp_socket));
}

int broadcast_message(broadcast_socket_t* broadcast_socket, const char* message) {
    return send_message(&(broadcast_socket->udp_socket), message);
}

int create_listener_socket(listener_socket_t* listener_socket, int port,
    size_t timeout_milliseconds) {

    udp_socket_t* udp_socket = &(listener_socket->udp_socket);

    if (create_udp_socket(udp_socket, NULL, port) != 0) {
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
    if (turn_on_socket_option(udp_socket, SO_REUSEPORT) != 0) {
        destroy_listener_socket(listener_socket);
        return -1;
    }

    if (bind_to_address(udp_socket) != 0) {
        destroy_listener_socket(listener_socket);
        return -1;
    }

    if (set_receive_timeout(udp_socket, timeout_milliseconds) != 0) {
        destroy_listener_socket(listener_socket);
        return -1;
    }

    return 0;
}

void destroy_listener_socket(listener_socket_t* listener_socket) {
    destroy_udp_socket(&(listener_socket->udp_socket));
}

int receive_broadcast(listener_socket_t* listener_socket, char* message_buffer,
    size_t message_buffer_size) {
    if (message_buffer_size == 0) {
        return 0;
    }

    int message_length = receive_message(&(listener_socket->udp_socket),
        message_buffer, message_buffer_size-1);
    if (message_length == -1) {
        return -1;
    }

    message_buffer[message_length] = '\0';
    return message_length + 1;
}
