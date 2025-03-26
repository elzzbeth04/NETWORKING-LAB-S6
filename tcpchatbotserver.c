#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = read(client_sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Client: %s\n", buffer);
        
        // Echo back to the client
        send(client_sock, buffer, strlen(buffer), 0);
    }

    printf("Client disconnected.\n");
    close(client_sock);
}

int main() {
    int sockfd, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(sockfd, (struct sockaddr *)&client, &client_len);
        printf("New client connected!\n");

        if (fork() == 0) {
            // Child process handles client
            close(sockfd);
            handle_client(client_sock);
            exit(0);
        }
        close(client_sock);
    }

    close(sockfd);
    return 0;
}