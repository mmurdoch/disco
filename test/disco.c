#include <disco/broadcast.h>
#include <disco/time.h>
#include <stdio.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>
#include <uuid/uuid.h>

/**
 * Creates a universally unique identifier (UUID) as a null-terminated 32
 * character string.
 *
 * @return created uuid string or NULL on failure
 */
char* create_uuid_string() {
    static char hex_chars[] = "0123456789ABCDEF";

    char* uuid_string = malloc(sizeof(uuid_t)*2 + 1);
    uuid_t uuid;
    uuid_generate(uuid);

    int i;
    for (i = 0; i < sizeof(uuid_t); i++) {
        uuid_string[i*2 + 0] = hex_chars[uuid[i] >> 4];
        uuid_string[i*2 + 1] = hex_chars[uuid[i] & 15];
    }
    uuid_string[i*2] = '\0';

    return uuid_string;
}

/**
 * Destroys a UUID string created by create_uuid_string().
 *
 * @param uuid_string UUID string to destroy
 */
void destroy_uuid_string(char* uuid_string) {
    free(uuid_string);
}

typedef struct peer_t peer_t;

struct peer_t {
    char* uuid_string;
    peer_t* next;
};

int main() {
    broadcast_socket_t broadcast_socket;
    listener_socket_t listener_socket;

    int port = 4950;

    if (create_broadcast_socket(&broadcast_socket, port, 100) != 0) {
        fprintf(stderr, "Failed to create broadcasting socket\n");
        return 1;
    }

    if (create_listener_socket(&listener_socket, port, 100) != 0) {
        fprintf(stderr, "Failed to create broadcast listening socket\n");
        return 1;
    }

    char* uuid_string = create_uuid_string();
    if (uuid_string == NULL) {
        fprintf(stderr, "Failed to create UUID\n");
        return 1;
    }

    peer_t me = {0};
    me.uuid_string = uuid_string;

    for (int i = 0; i < 100; i++) {
        if (broadcast_message(&broadcast_socket, uuid_string) < 0) {
            fprintf(stderr, "Failed to send broadcast message\n");
            destroy_uuid_string(uuid_string);
            destroy_listener_socket(&listener_socket);
            destroy_broadcast_socket(&broadcast_socket);
            return 1;
        }

        printf("Broadcasted ID: %s\n", uuid_string);

        size_t message_buffer_size = 100;
        char message_buffer[message_buffer_size];

        for (int j = 0; j < 10; j++) {
            int received_message_length = receive_broadcast(&listener_socket,
                message_buffer, message_buffer_size);
            if (received_message_length == -1) {
                sleep_milliseconds(100);
            } else {
                if (strcmp(message_buffer, me.uuid_string) != 0) {
                    printf("Peer found:     %s\n", message_buffer);
                }
            }
        }

        sleep_milliseconds(100);
    }

    destroy_uuid_string(uuid_string);
    destroy_listener_socket(&listener_socket);
    destroy_broadcast_socket(&broadcast_socket);

    return 0;
}
