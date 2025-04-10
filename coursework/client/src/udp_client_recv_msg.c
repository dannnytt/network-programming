#include "udp_client.h"

void udp_client_recv_msg(udp_client_t *client, char *buffer, size_t buffer_size) {
    
    ssize_t recvd_bytes = recvfrom(client->sockfd, buffer, buffer_size - 1, 0,
                                    (struct sockaddr*) &client->server_addr, 
                                    &client->server_addr_len);

    if (recvd_bytes < 0) {
        perror("Ошибка: сообщение не получено.\n");
        return;
    }

    buffer[recvd_bytes] = '\0';
    printf("(Сервер): %s\n", buffer);
}
