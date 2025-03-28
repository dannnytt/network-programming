#ifndef MT_TCP_SERVER_H
#define MT_TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_LISTEN_QUEUE 5

typedef struct mt_tcp_server {
    int sockfd;
    struct sockaddr_in server_addr;

} mt_tcp_server;


void mt_tcp_server_init(mt_tcp_server *server);
void mt_tcp_server_run(mt_tcp_server *server);
void mt_tcp_server_destroy(mt_tcp_server *server);

void *client_handler(void *arg);
int mt_tcp_server_recvmsg(int connfd, char *msg_buf, size_t buf_size);
void mt_tcp_server_sendmsg(int connfd, char *msg_buf);

#endif // MT_TCP_SERVER_H