#include "udp_server.h"

void udp_server_destroy(udp_server_t *server) {
    close(server->sockfd);
}
