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

char* create_identification_broadcast_message() {
    char* protocol_id = "DSC";
    char* protocol_version = "1.0";
    char* uuid_string = create_uuid_string();
    char* greeting_message = "HERE";

    int protocol_id_length = strlen(protocol_id);
    int protocol_version_length = strlen(protocol_version);
    int uuid_string_length = strlen(uuid_string);
    int greeting_message_length = strlen(greeting_message);
    int message_length = protocol_id_length +
        protocol_version_length + uuid_string_length +
        greeting_message_length + 1;
    char* message = (char*) malloc(sizeof(char) * message_length);
    if (message == NULL) {
        return NULL;
    }

    snprintf(message, message_length, "%s%s%s%s",
        protocol_id, protocol_version, uuid_string, greeting_message);

    destroy_uuid_string(uuid_string);

    return message;
}

void destroy_identification_broadcast_message(char* message) {
    free(message);
}

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

    char* message = create_identification_broadcast_message();
    if (message == NULL) {
        fprintf(stderr, "Failed to create identification message\n");
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        if (broadcast_message(&broadcast_socket, message) < 0) {
            fprintf(stderr, "Failed to send broadcast message\n");
            destroy_identification_broadcast_message(message);
            destroy_broadcast_socket(&broadcast_socket);
            return 1;
        }

        printf("Broadcasted message: %s\n", message);

        size_t message_buffer_size = 100;
        char message_buffer[message_buffer_size];

        for (int j = 0; j < 10; j++) {
            int received_message_length = receive_broadcast(&listener_socket,
                message_buffer, message_buffer_size);
            if (received_message_length == -1) {
                sleep_milliseconds(100);
            } else {
                printf("Received message:    %s\n", message_buffer);
            }
        }

        sleep_milliseconds(100);
    }

    destroy_identification_broadcast_message(message);
    destroy_listener_socket(&listener_socket);
    destroy_broadcast_socket(&broadcast_socket);

    return 0;
}
