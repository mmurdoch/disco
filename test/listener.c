#include <stdio.h>

#include <disco/udp.h>
#include <disco/broadcast.h>

int main() {
    udp_socket_t listener_socket;
    int port = 4950;

    if (create_listener_socket(&listener_socket, 4950, 1000) != 0) {
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

    destroy_listener_socket(&listener_socket);

    return 0;
}
