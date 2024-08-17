#include "client.h"

int main() {
    int sockfd = create_socket();
    
    // Implement your client logic here

    cleanup_socket(sockfd);
    return 0;
}
