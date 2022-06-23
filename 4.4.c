#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int connfd)
{
        char buffer[MAX];
        int n;
        // infinite loop for chat
        for (;;) {
                bzero(buffer, MAX);

                // read the message from client and copy it in buffer
                read(connfd, buffer, sizeof(buffer));
                // print buffer which contains the client contents
                printf("From client: %s\t To client : ", buffer);
                bzero(buffer, MAX);
                n = 0;
                // copy server message in the buffer
                while ((buffer[n++] = getchar()) != '\n')
                        ;

                // and send that buffer to client
                write(connfd, buffer, sizeof(buffer));

                // if msg contains "Exit" then server exit and chat ended.
                if (strncmp("exit", buffer, 4) == 0) {
                        printf("[-]Server Exit...\n");
                        break;
                }
        }
}

// Driver function
int main()
{
        int sockfd, connfd, len;
        struct sockaddr_in servaddr, cli;

        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                printf("[-]Error in connection. \n");
                exit(0);
        }
        else
                printf("[+]Server Socket is created. \n");
        bzero(&servaddr, sizeof(servaddr));

        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);

        // Binding newly created socket to given IP and verification
        if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
                printf("[-]Error in binding. \n");
                exit(0);
        }
        else
                printf("[+]Socket successfully binded..\n");

        // Now server is ready to listen and verification
        if ((listen(sockfd, 5)) != 0) {
                printf("[-]Error in listening...\n");
                exit(0);
        }
        else
                printf("[+]Listening... \n");
        len = sizeof(cli);

        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
                printf("[-]Connection failed...\n");
                exit(0);
        }
        else
                printf("[+]Server accept connection from client...\n");

        // Function for chatting between client and server
        func(connfd);

        // After chatting close the socket
        close(sockfd);
}
