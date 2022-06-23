#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX 80
#define PORT 8888
#define SA struct sockaddr
void func(int sockfd)
{
        char buffer[MAX];
        int n;
        for (;;) {
                bzero(buffer, sizeof(buffer));
                printf("Enter the string : ");
                n = 0;
                while ((buffer[n++] = getchar()) != '\n')
                        ;
                write(sockfd, buffer, sizeof(buffer));
                bzero(buffer, sizeof(buffer));
                read(sockfd, buffer, sizeof(buffer));
                printf("From Server : %s", buffer);
                if ((strncmp(buffer, "exit", 4)) == 0) {
                        printf("[-]Disconnected from server. \n");
                        break;
                }
        }
}

int main()
{
        int sockfd, connfd;
        struct sockaddr_in servaddr, cli;

        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                printf("[-]socket creation failed...\n");
                exit(0);
        }
        else
                printf("[+]Socket successfully created..\n");
        bzero(&servaddr, sizeof(servaddr));

        // assign IP, PORT
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("192.168.56.103");
        servaddr.sin_port = htons(PORT);

        // connect the client socket to server socket
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
                printf("[-]Error in connection...\n");
                exit(0);
        }
        else
                printf("[+]Connected to the server..\n");

        // function for chat
        func(sockfd);

        // close the socket
        close(sockfd);
}
