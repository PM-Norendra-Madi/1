#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h> // Include this header for inet_pton

int main()
{
    int welcomeSocket, newSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // Create the socket
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if (listen(welcomeSocket, 5) == 0)
        printf("Listening to Client....\n");
    else
        printf("Error\n");

    addr_size = sizeof serverStorage;
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    // Receive a message from the client
    recv(newSocket, buffer, 1024, 0);
    printf("Client says: %s\n", buffer);

    // Send "Hello" to the client
    strcpy(buffer, "Hello");
    send(newSocket, buffer, strlen(buffer), 0);

    return 0;
}

