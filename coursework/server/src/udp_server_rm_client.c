#include "udp_server.h"

void udp_server_rm_client(udp_server_t *server, struct sockaddr_in *addr) {
    for (int i = 0; i < server->client_count; i++) {
        if (memcmp(&server->clients[i], addr, sizeof(struct sockaddr_in)) == 0) {
            for (int j = i; j < server->client_count - 1; j++) {
                server->clients[j] = server->clients[j + 1];
            }
            
            server->client_count--;
            break;
        }
    }
}
