#include <stdio.h>

#include <disco/broadcast.h>


int main() {
    listener_socket_t listener_socket;
    int port = 4950;

    if (create_listener_socket(&listener_socket, 4950, 1000) != 0) {
        fprintf(stderr, "Failed to create broadcast listening socket\n");
        return 1;
    }

    size_t message_buffer_size = 100;
    char message_buffer[message_buffer_size];

    int message_length = receive_broadcast(&listener_socket,
        message_buffer, message_buffer_size);
    if (message_length < 0) {
        destroy_listener_socket(&listener_socket);
        fprintf(stderr, "Failed to receive broadcast message\n");
        return 1;
    }

    printf("%s", message_buffer);

    destroy_listener_socket(&listener_socket);

    return 0;
}
