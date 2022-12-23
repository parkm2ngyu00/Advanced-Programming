# 소켓 프로그래밍 (Socket Programming)

- 네트워크를 통해 프로그램 간 메시지를 전달하는 방법
- 일반적으로 서버와 클라이언트가 각자의 소켓을 통해 메시지를 교환

    - 서버/클라이언트 구조가 아닌 Peer-to-peer 형태로 소켓 통신을 할 수도 있음

    ![](https://images.velog.io/images/funnysunny08/post/5e30bb88-cb61-4ed1-a48f-af587b7e0aed/%EB%8B%A4%EC%9A%B4%EB%A1%9C%EB%93%9C.png)

## 소켓의 종류

- 요청 여부
    - 클라이언트 소켓
    - 서버 소켓

- 연결 형태
    - TCP (Connection-oriented protocol) - Stream 소켓
    - UDP (Connectionless protocol) - Datagram 소켓

## 소켓 연결 흐름

![](https://t1.daumcdn.net/cfile/tistory/995C23465C7DD7E30B)

- 서버

    - 소켓을 생성한다
    - 서버가 사용할 IP주소와 포트번호를 생성한 소켓에 결합한다 (bind)
    - 클라이언트로부터의 요청을 기다린다 (listen)
    - 요청이 들어오면 요청을 받아드리며 (accept) 클라이언트와의 통신을 위한 새로운 소켓을 생성한다
    - 새로 생성된 소켓을 통해 클라이언트와 데이터를 송수신한다 (send/receive)
    - 데이터 송수신이 완료되면, 소켓을 닫는다 (close)

- 클라이언트

    - 소켓을 생성한다
    - 서버 측에 연결을 요청한다 (connect)
    - 서버로 부터 연결이 받아지면 생성한 소켓을 통해 데이터를 송수신한다 (send/receive)
    - 데이터 송수신이 완료되면, 소켓을 닫는다 (close)

## 다중 클라이언트 처리 (server-side)

- 멀티 프로세싱

    ![](https://jongmin92.github.io/images/post/2019-02-21/multi_process_server.png)

- 멀티 스레딩

    ![](https://csharpcorner-mindcrackerinc.netdna-ssl.com/UploadFile/433c33/multithreaded-sockets-multithreaded-server-and-working-wit/Images/multithreading7.JPG)

## 소켓 프로그래밍 예제

- Echo Server ([practice/11/echo/server.c](../../practice/11/echo/server.c))

    ```
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
            close(server_sock);
            return -1;
        }

        // wait for connections (concurrent connection = 5)
        if (listen(server_sock, 5) == -1) {
            printf("Failed to listen the socket\n");
            close(server_sock);
            return -1;
        }

        client_addr_size = sizeof(client_addr);

        // accept a new connection
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_sock == -1) {
            printf("Failed to accept a new connection\n");
            close(server_sock);
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
    ```

    - 컴파일 및 실행

        ```
        $ gcc -o server server.c
        $ ./server 8080 # 8080 포트 오픈
        ```

- Echo Client ([practice/11/echo/client.c](../../practice/11/echo/client.c))

    ```
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
            close(sock);
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
    ```

    - 컴파일 및 실행

        ```
        $ gcc -o client client.c
        $ ./server 127.0.0.1 8080 # 서버 접속
        ```
