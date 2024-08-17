#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

int create_socket();
void handle_error(const char *message);
void cleanup_socket(int sockfd);

#endif
