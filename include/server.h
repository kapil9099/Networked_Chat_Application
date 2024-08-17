#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm> // For std::remove

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

#include "network_utils.h"
#include <iostream> // Include for std::cout
#include <string>   // Include for std::string

class Server {
public:
    Server();              // Constructor
    void run();            // Start the server loop
    void acceptConnection(); // Accept a new connection
    void handleClient(int client_socket); // Handle a client request
    void broadcastMessage(int sender_socket, const std::string &message); // Broadcast a message to all clients
    void closeServer();    // Close all sockets and cleanup

private:
    int server_fd;          // Server socket file descriptor
    std::vector<int> client_sockets; // List of client sockets
};

#endif // SERVER_H

