#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct tcp_client {
    int sockfd;
    struct sockaddr_in client_addr;

    char client_ip[INET_ADDRSTRLEN];
    uint16_t client_port;

    char server_ip[INET_ADDRSTRLEN];
    uint16_t server_port;

} tcp_client;

void tcp_client_init(tcp_client *client, char *server_ip, uint16_t server_port);
void tcp_client_run(tcp_client *client);
void tcp_client_destroy(tcp_client *client);

void tcp_client_recvmsg(tcp_client *client, char *msg_buf, size_t buf_size);
void tcp_client_sendmsg(tcp_client *client, char *msg_buf);

#endif // TCP_CLIENT_H