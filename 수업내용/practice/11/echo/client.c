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
    int sock;
    struct sockaddr_in server_addr;

    char message[BUFSIZE];
    int msg_len;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        return -1;
    }

    // create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Failed to create a socket\n");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        printf("Failed to to connect the server\n");
        return -1;
    }

    while (1) {
        // get a message
        fputs("Type the message to send (q to quit): ", stdout);
        fgets(message, BUFSIZE, stdin);

        if (strcmp(message, "q\n") == 0) {
            break;
        }

        // send the message
        write(sock, message, strlen(message));

        // receive a message
        msg_len = read(sock, message, BUFSIZE-1);

        message[msg_len] = 0;
        printf("Received message: %s", message);
    }

    // close the connection
    close(sock);

    return 0;
}
