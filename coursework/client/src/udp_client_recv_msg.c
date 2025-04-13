#include "udp_client.h"

void udp_client_recv_msg(udp_client_t *client, char *buffer, size_t buffer_size) {
    
    socklen_t server_addr_len = sizeof(client->server_addr);
    
    ssize_t recvd_bytes = recvfrom(
        client->sockfd, 
        buffer, 
        buffer_size - 1, 
        0,
        (struct sockaddr*)&client->server_addr, 
        &server_addr_len
    );

    if (recvd_bytes > 0) {
        buffer[recvd_bytes] = '\0';
    }    
    else perror("Ошибка при вызове 'recvfrom'");
}
