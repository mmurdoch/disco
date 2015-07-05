#include <stdio.h>

#include "network.h"

int create_broadcast_listener_socket(udp_socket_t* socket, int port,
    size_t timeout_milliseconds) {

    if (create_udp_socket(socket, NULL, port) == -1) {
        return -1;
    }

    /* Setting SO_REUSEADDR is not needed on Mac OS X (any BSD?) to allow
       multiple copies of this program running on the same machine from
       receiving messages. It is probably needed on Windows. */
    /*if (turn_on_socket_option(listener_socket, SO_REUSEADDR) == -1) {
        destroy_udp_socket(socket);
        return -1;
    }*/

    /* Setting SO_REUSEPORT is needed on Mac OS X (any BSD?) to allow multiple
       copies of this program running on the same machine from receiving messages.
       Windows systems do not recognize this setting. What about Linux? What
       about Solaris? */
    if (turn_on_socket_option(*socket, SO_REUSEPORT) == -1) {
        destroy_udp_socket(socket);
        return -1;
    }

    if (bind_to_address(*socket) == -1) {
        destroy_udp_socket(socket);
        return -1;
    }

    time_t seconds = timeout_milliseconds/1000;
    suseconds_t microseconds = (timeout_milliseconds-(1000*seconds))*1000;
    if (set_receive_timeout(*socket, seconds, microseconds) == -1) {
        destroy_udp_socket(socket);
        return -1;
    }

    return 0;
}

int main() {
    udp_socket_t listener_socket;
    int port = 4950;

    if (create_broadcast_listener_socket(&listener_socket, 4950, 1000) != 0) {
        fprintf(stderr, "Failed to create broadcast listening socket\n");
        return 2;
    }

    size_t max_message_length = 100;
    char message[max_message_length+1];

    int message_length = receive_message(listener_socket,
        message, max_message_length);
    if (message_length == -1) {
        destroy_udp_socket(&listener_socket);
        fprintf(stderr, "Failed to receive broadcast message\n");
        return 2;
    }

    message[message_length] = '\0';
    printf("%s", message);

    destroy_udp_socket(&listener_socket);

    return 0;
}
