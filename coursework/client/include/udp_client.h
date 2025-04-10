#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct udp_client {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;

} udp_client_t;


void udp_client_init(udp_client_t *client, const char *server_addr, uint16_t server_port);
void udp_client_run(udp_client_t *client);
void udp_client_destroy(udp_client_t *client);

void udp_client_send_msg(udp_client_t *client, const char *message);
void udp_client_recv_msg(udp_client_t *client, char *buffer, size_t buffer_size);


#endif // UDPCLIENT_H