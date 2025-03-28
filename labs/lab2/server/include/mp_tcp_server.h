#ifndef MP_TCP_SERVER_H
#define MP_TCP_SERVER_H

#define MAX_LISTEN_QUEUE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

typedef struct mp_tcp_server {
    int sockfd;
    struct sockaddr_in server_addr;

} mp_tcp_server;

void mp_tcp_server_init(mp_tcp_server *server);
void mp_tcp_server_run(mp_tcp_server *server);
void mp_tcp_server_destroy(mp_tcp_server *server);

void mp_tcp_server_handle_client(int connfd);
int mp_tcp_server_recvmsg(int connfd, char *msg_buf, size_t buf_size);
void mp_tcp_server_sendmsg(int connfd, const char *msg_buf);

#endif // MP_TCP_SERVER_H