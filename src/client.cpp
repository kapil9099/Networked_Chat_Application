#include "client.h"

Client::Client() {
    sock = create_socket();

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8080); // Use the correct port

    if (sock < 0) {
        handle_error("Socket creation error");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        handle_error("Connection failed");
    }
}

void Client::run() {
    fd_set readfds;
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        int max_sd = sock > STDIN_FILENO ? sock : STDIN_FILENO;

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0) {
            handle_error("Select error");
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            sendMessage();
        }

        if (FD_ISSET(sock, &readfds)) {
            receiveMessage();
        }
    }
}

void Client::sendMessage() {
    std::string message;
    std::getline(std::cin, message);
    send(sock, message.c_str(), message.size(), 0);
}

void Client::receiveMessage() {
    char buffer[1024] = {0};
    int valread = recv(sock, buffer, 1024, 0);  // Use recv instead of read on Windows
    if (valread > 0) {
        std::string message(buffer, valread);
        std::cout << "Server: " << message << std::endl;
    }
}
