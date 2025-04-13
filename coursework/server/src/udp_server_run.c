#include "udp_server.h"

void udp_server_run(udp_server_t *server) {

    socklen_t client_addr_len = sizeof(server->client_addr);
    char buffer[1024];

    while (true) {
        ssize_t recvd_bytes = recvfrom(
            server->sockfd,
            buffer,
            sizeof(buffer) - 1,
            0,
            (struct sockaddr*)&server->client_addr,
            &client_addr_len
        );
        
        buffer[recvd_bytes] = '\0';

        if (strcmp(buffer, "/quit") == 0) {
            udp_server_rm_client(server, &server->client_addr);
            continue;
        }

        if (!udp_server_has_client(server, &server->client_addr))
            server->clients[server->client_count++] = server->client_addr;

        for (int i = 0; i < server->client_count; i++) {
            udp_server_sendto(
                server, 
                &server->clients[i], 
                &server->client_addr, 
                buffer
            );
        }
    }
}
