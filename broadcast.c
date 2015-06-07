#include <errno.h>
#include <stdio.h>
#include <string.h>

void print_error(const char* message) {
    size_t message_length = strlen(message);
    char error_message[message_length + 7];
    strcpy(error_message, message);
    strcpy(error_message + message_length, " (%s)\n");
    fprintf(stderr, error_message, strerror(errno));
}

