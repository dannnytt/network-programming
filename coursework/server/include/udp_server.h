#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10

typedef struct udp_server {
    int sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct sockaddr_in clients[MAX_CLIENTS];
    int client_count;

} udp_server_t;

void udp_server_init(udp_server_t *server, const char* ip_addr);

void udp_server_destroy(udp_server_t *server);

void udp_server_run(udp_server_t *server);

void udp_server_sendto(
    udp_server_t *server, 
    const struct sockaddr_in *client_addr, 
    const struct sockaddr_in *sender_addr, 
    const char *msg
);


int udp_server_has_client(udp_server_t *server, struct sockaddr_in *addr);

void udp_server_rm_client(udp_server_t *server, struct sockaddr_in *addr); 

#endif // UDPSERVER_H
