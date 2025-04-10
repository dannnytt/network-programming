#include "udp_server.h"

int udp_server_recv_msg(udp_server_t *server, char *buffer, size_t buffer_size) {

    socklen_t client_addr_len = sizeof(server->client_addr);
    ssize_t recvd = recvfrom(server->sockfd, buffer, buffer_size - 1, 0,
                                    (struct sockaddr*) &server->client_addr, 
                                    &client_addr_len);

    if (recvd < 0) {
        perror("Ошибка: сообщение не получено.\n");
        return 1;
    }
    
    buffer[recvd] = '\0';
    
    
    char client_ip[INET_ADDRSTRLEN];
    uint16_t client_port;
    get_client_ip(&server->client_addr, client_ip, sizeof(client_ip));
    get_client_port(&server->client_addr, &client_port);


    printf("[Клиент %s:%d]: %s\n", client_ip, client_port, buffer);
    return 0;
}
