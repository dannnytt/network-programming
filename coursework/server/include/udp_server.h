#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct udp_server {
    int sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

} udp_server_t;


void udp_server_init(udp_server_t *server, const char* ip_addr);
void udp_server_run(udp_server_t *server);
void udp_server_destroy(udp_server_t *server);

void udp_server_send_msg(udp_server_t *server, const char* message);
int udp_server_recv_msg(udp_server_t *server, char *buffer, size_t buffer_size);

void get_client_ip(struct sockaddr_in *client_addr, char *client_ip, size_t buf_size);
void get_client_port(struct sockaddr_in *client_addr, uint16_t *client_port);

#endif // UDPSERVER_H