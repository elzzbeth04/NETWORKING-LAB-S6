#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

// Function to check if a number is Armstrong
int is_armstrong(int num) {
    int originalNum = num, sum = 0, digits = 0, remainder;

    // Count number of digits
    while (originalNum != 0) {
        originalNum /= 10;
        digits++;
    }

    originalNum = num;
    
    // Calculate sum of power of digits
    while (originalNum != 0) {
        remainder = originalNum % 10;
        sum += pow(remainder, digits);
        originalNum /= 10;
    }

    return (sum == num);
}

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char result[50];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Define server properties
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Read number from client
    valread = read(new_socket, buffer, 1024);
    int num = atoi(buffer);

    // Check Armstrong number
    if (is_armstrong(num)) {
        strcpy(result, "Armstrong");
    } else {
        strcpy(result, "Not Armstrong");
    }

    // Send result to client
    send(new_socket, result, strlen(result), 0);
    printf("Processed number %d: %s\n", num, result);

    // Close connection
    close(new_socket);
    close(server_fd);
    
    return 0;
}
