#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <arpa/inet.h>
#include <netinet/in.h>

void get_client_ip(struct sockaddr_in *client_addr, char *client_ip, size_t buf_size);
void get_client_port(struct sockaddr_in *client_addr, uint16_t *client_port);

#endif // NET_UTILS_H