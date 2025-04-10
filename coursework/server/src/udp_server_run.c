#include "udp_server.h"

void udp_server_run(udp_server_t *server) {
    
    char response[1024];

    while (1) {
        
        if (udp_server_recv_msg(server, response, sizeof(response)) < 0)
            continue;

        if (strcmp(response, "exit") == 0) {
            char client_ip[INET_ADDRSTRLEN];
            uint16_t client_port;
            get_client_ip(&server->client_addr, client_ip, sizeof(client_ip));
            get_client_port(&server->client_addr, &client_port);

            printf("[Клиент %s:%d]: отключился\n", client_ip, client_port);
            continue;
        }

        udp_server_send_msg(server, response);
    }
}
