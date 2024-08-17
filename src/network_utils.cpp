#include "network_utils.h"

int create_socket() {
    #ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            handle_error("WSAStartup failed");
        }
    #endif

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        handle_error("Socket creation failed");
    }
    return sockfd;
}

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void cleanup_socket(int sockfd) {
    #ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
    #else
        close(sockfd);
    #endif
}

