#include "net_utils.h"

void get_client_ip(struct sockaddr_in *client_addr, char *client_ip, size_t buf_size) {
    inet_ntop(AF_INET, &client_addr->sin_addr, client_ip, buf_size);
}

void get_client_port(struct sockaddr_in *client_addr, uint16_t *client_port) {
    *client_port = ntohs(client_addr->sin_port);
}