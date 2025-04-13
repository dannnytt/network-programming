#include <udp_server.h>

int udp_server_has_client(udp_server_t *server, struct sockaddr_in *addr) {
    for (int i = 0; i < server->client_count; i++) {
        if (memcmp(&server->clients[i], addr, sizeof(struct sockaddr_in)) == 0) {
            return true;
        }
    }
    
    return false;
}
