#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef struct udp_client {
    int sockfd;
    struct sockaddr_in server_addr;

} udp_client_t;


void udp_client_init(
    udp_client_t *client, 
    const char *server_addr, 
    uint16_t server_port
);

void udp_client_destroy(udp_client_t *client);

void udp_client_run(udp_client_t *client);

void udp_client_send_msg( udp_client_t *client, const char *message);

void udp_client_recv_msg(
    udp_client_t *client, 
    char *buffer, 
    size_t buffer_size
); 

void get_ip(
    struct sockaddr_in *client_addr, 
    char *client_ip, 
    size_t buf_size
);

void get_port(struct sockaddr_in *client_addr, uint16_t *client_port);

void* udp_client_recv_thread(void* arg);
void* udp_client_send_thread(void* arg);


#endif // UDPCLIENT_H
