#include "udp_server.h"

void udp_server_send_msg(udp_server_t *server, const char *message) {
    
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", message);

    ssize_t sent = sendto(server->sockfd, buffer, strlen(buffer), 0,
                                (struct sockaddr*) &server->client_addr, 
                                sizeof(server->client_addr));

    if (sent < 0)
        perror("Ошибка: сообщение не отправлено.\n");
}
