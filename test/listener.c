#include <stdio.h>

#include <disco/udp.h>

void destroy_broadcast_listener_socket(udp_socket_t* listener_socket);

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
