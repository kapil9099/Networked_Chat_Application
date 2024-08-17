#ifndef CLIENT_H
#define CLIENT_H

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

#include "network_utils.h"
#include <iostream>  // Include for std::cout, std::cin
#include <string>    // Include for std::string

class Client {
public:
    Client();              // Constructor
    void run();            // Start the client loop
    void sendMessage();    // Send a message to the server
    void receiveMessage(); // Receive a message from the server

private:
    int sock;              // Client socket
    struct sockaddr_in serv_addr; // Server address
};

#endif
