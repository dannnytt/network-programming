#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <arpa/inet.h>  
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 

#define BUFLEN 512

int main(int argc, char *argv[])
{
    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);
    
    int sockfd;
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // устанавливаем соединение с сервером.
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    
    
    int i = 1;
    int loop_count = 10;
    char buffer[BUFLEN];
    for (int count = 0; count < loop_count; count++) {
        snprintf(buffer, BUFLEN, "%d", i);
        if (send(sockfd, buffer, strlen(buffer), 0) == -1) {
            perror("send");
            break;
        }
        printf("Sent: %s\n", buffer);
        sleep(i);
        i++;
    }

    close(sockfd);
    return 0;
}
