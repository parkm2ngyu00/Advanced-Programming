#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    int server_sock, client_sock;

    char message[BUFSIZE];
    int msg_len;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int client_addr_size;

    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        return -1;
    }

    // create a socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        printf("Failed to create a socket\n");
        return -1;
    }
 
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // assign the address and port to the socket
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Failed to bind the socket\n");
        return -1;
    }

    // wait for connections (concurrent connection = 5)
    if (listen(server_sock, 5) == -1) {
        printf("Failed to listen the socket\n");
        return -1;
    }

    client_addr_size = sizeof(client_addr);

    // accept a new connection
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock == -1) {
        printf("Failed to accept a new connection\n");
        return -1;
    }

    // read and write messages through the socket
    while ((msg_len = read(client_sock, message, BUFSIZE)) != 0) {
        message[msg_len] = 0;
        write(client_sock, message, msg_len);
        printf("Received message: %s", message);
    }

    // close the connection
    close(client_sock);

    return 0;
}
