#include "server.h"

Server::Server() {
    server_fd = create_socket();

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        handle_error("Bind failed");
    }

    if (listen(server_fd, 3) < 0) {
        handle_error("Listen failed");
    }
}

void Server::run() {
    fd_set readfds;
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        int max_sd = server_fd;

        for (int client_socket : client_sockets) {
            FD_SET(client_socket, &readfds);
            if (client_socket > max_sd) {
                max_sd = client_socket;
            }
        }

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            handle_error("Select error");
        }

        if (FD_ISSET(server_fd, &readfds)) {
            acceptConnection();
        }

        for (int client_socket : client_sockets) {
            if (FD_ISSET(client_socket, &readfds)) {
                handleClient(client_socket);
            }
        }
    }
}

void Server::acceptConnection() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        handle_error("Accept failed");
    }

    client_sockets.push_back(new_socket);
    std::cout << "New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
}

void Server::broadcastMessage(int sender_socket, const std::string &message) {
    for (int client_socket : client_sockets) {
        if (client_socket != sender_socket) {
            send(client_socket, message.c_str(), message.size(), 0);
        }
    }
}

void Server::handleClient(int client_socket) {
    char buffer[1024] = {0};
    int valread = recv(client_socket, buffer, 1024, 0);  // Use recv instead of read on Windows
    if (valread == 0) {
        closesocket(client_socket);  // Use closesocket instead of close on Windows
        client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end());
        std::cout << "Client disconnected" << std::endl;
    } else {
        std::string message(buffer, valread);
        std::cout << "Received: " << message << std::endl;
        broadcastMessage(client_socket, message);
    }
}

void Server::closeServer() {
    for (int client_socket : client_sockets) {
        closesocket(client_socket);  // Use closesocket instead of close on Windows
    }
    closesocket(server_fd);  // Use closesocket instead of close on Windows
}


