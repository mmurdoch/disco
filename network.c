#include "network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int decimal_string_length(int i) {
    /* Include space for terminating null */
    int length = 1;

    if (i <= 0) {
        length++;
    }

    int current = abs(i);

    while (current > 0) {
        current /= 10;
        length++;
    }

    return length;
}

void port_to_string(int port, char* port_string) {
    int port_string_length = decimal_string_length(port);

    snprintf(port_string, port_string_length, "%d", port);
}

int create_udp_socket(udp_socket_t* the_socket, const char* ip_address,
    int port) {

    int port_string_length = decimal_string_length(port);
    char port_string[port_string_length];
    port_to_string(port, port_string);

    struct addrinfo hints;
    struct addrinfo* all_addresses;
    struct addrinfo* current;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    if (ip_address == NULL) {
        hints.ai_flags = AI_PASSIVE;
    }

    if (getaddrinfo(ip_address, port_string, &hints, &all_addresses) != 0) {
        return -1;
    }

    int current_socket = -1;
    for (current = all_addresses; current != NULL; current = current->ai_next) {
        current_socket = socket(
            current->ai_family, current->ai_socktype, current->ai_protocol);
        if (current_socket != -1) {
            break;
        }
    }

    if (current == NULL) {
        return -1;
    }

    the_socket->all_addresses = all_addresses;
    the_socket->socket_address = current;
    the_socket->socket = current_socket;

    return 0;
}

void destroy_udp_socket(udp_socket_t* the_socket) {
    close(the_socket->socket);
    freeaddrinfo(the_socket->all_addresses);
}

int turn_on_socket_option(udp_socket_t* socket, int option_name) {
    int turn_on = 1;
    return setsockopt(socket->socket, SOL_SOCKET, option_name,
        &turn_on, sizeof(turn_on));
}

int set_receive_timeout(udp_socket_t* socket, time_t seconds,
    suseconds_t microseconds) {
    struct timeval timeout;
    timeout.tv_sec = seconds;
    timeout.tv_usec = microseconds;

    return setsockopt(socket->socket, SOL_SOCKET, SO_RCVTIMEO,
        &timeout, sizeof(timeout));
}

in_port_t get_port_from_sockaddr(struct sockaddr* address) {
    if (address->sa_family == AF_INET) {
        return (((struct sockaddr_in*)address)->sin_port);
    }

    return (((struct sockaddr_in6*)address)->sin6_port);
}

int get_socket_handle(udp_socket_t* socket) {
    return socket->socket;
}

struct sockaddr* get_address(udp_socket_t* socket) {
    return socket->socket_address->ai_addr;
}

socklen_t get_address_length(udp_socket_t* socket) {
    return socket->socket_address->ai_addrlen;
}

int get_port(udp_socket_t* socket) {
    return ntohs(get_port_from_sockaddr(get_address(socket)));
}

int send_message(udp_socket_t* socket, const char* message) {
    return sendto(get_socket_handle(socket), message, strlen(message), 0,
        get_address(socket), get_address_length(socket));
}

int bind_to_address(udp_socket_t* socket) {
    return bind(get_socket_handle(socket), get_address(socket),
        get_address_length(socket));
}

int receive_message(udp_socket_t* socket, char* message,
    size_t max_message_length) {
    struct sockaddr_storage sent_from_address;
    socklen_t sent_from_address_length = sizeof(sent_from_address);

    return recvfrom(get_socket_handle(socket),
        message, max_message_length-1 , 0,
        (struct sockaddr *) &sent_from_address, &sent_from_address_length);
}
