#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket;
    struct sockaddr_in server_addr;
    char buffer[1024] = "Hello from client";
    char response[1024];
    socklen_t len = sizeof(server_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address configuration
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address

    // Send message to server
    sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, len);
    printf("Message sent to server\n");

    // Receive response from server
    recvfrom(server_socket, response, sizeof(response), 0, (struct sockaddr *)&server_addr, &len);
    printf("Message from server: %s\n", response);

    close(server_socket);
    return 0;
}