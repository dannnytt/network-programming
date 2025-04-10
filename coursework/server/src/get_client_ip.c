#include "udp_server.h"

void get_client_ip(struct sockaddr_in *client_addr, char *client_ip, size_t buf_size) {
    inet_ntop(AF_INET, &client_addr->sin_addr, client_ip, buf_size);
}
