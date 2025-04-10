#include "udp_server.h"

void get_client_port(struct sockaddr_in *client_addr, uint16_t *client_port) {
    *client_port = ntohs(client_addr->sin_port);
}
