#include "udp_client.h"

void udp_client_send_msg(udp_client_t *client, const char* message) {
    
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", message);

    ssize_t sent_bytes = sendto(client->sockfd, buffer, strlen(buffer), 0, 
                                (struct sockaddr*) &client->server_addr, 
                                client->server_addr_len);
    
    if (sent_bytes < 0)
        perror("Ошибка: сообщение не отправлено.\n");

}
