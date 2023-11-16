#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("inet_pton");
        return 1;
    }

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    // Send "Hello" to the server
    strcpy(buffer, "Hello");
    send(clientSocket, buffer, strlen(buffer), 0);
    printf("Message Sent to Server....\n");
    
    // Receive a message from the server
    recv(clientSocket, buffer, 1024, 0);
    printf("Server says: %s\n", buffer);

    return 0;
}
