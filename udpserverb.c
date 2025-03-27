#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t len = sizeof(client_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address configuration
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    

    // Bind the socket to the server address
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Waiting for data...\n");

    // Receive data from client
    recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &len);
    printf("Message from client: %s\n", buffer);

    // Respond to client
    sendto(server_socket, "Hello from server", 18, 0, (struct sockaddr *)&client_addr, len);

    close(server_socket);
    return 0;
}