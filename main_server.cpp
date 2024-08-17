#include "server.h"

int main() {
    int sockfd = create_socket();  // Create a socket using the function from network_utils.cpp
    
    // Implement your server logic here
    
    cleanup_socket(sockfd);  // Clean up the socket before exiting
    return 0;
}

