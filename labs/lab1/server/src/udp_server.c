#include "udp_server.h"
#include "net_utils.h"
#include "str_utils.h"

void udp_server_init(udp_server_t *server, const char *ip_addr) {

    server->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (server->sockfd < 0) {
        perror("Ошибка: сокет сервера не создан.\n");
        exit(EXIT_FAILURE);
    }
    
    memset(&server->server_addr, 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    // server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = 0;

    if (inet_pton(AF_INET, ip_addr, &server->server_addr.sin_addr) <= 0) {
        perror("Ошибка: IP-адрес сервера не преобразован.\n");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }
    
    socklen_t server_addr_len = sizeof(server->server_addr);
    if (bind(server->sockfd, (struct sockaddr*) &server->server_addr, server_addr_len) < 0) {
        perror("Ошибка: привязка сокета прошла неудачно.\n");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    if (getsockname(server->sockfd, (struct sockaddr*) &server->server_addr, &server_addr_len) == -1) {
        perror("Ошибка: порт не получен.\n");
        close(server->sockfd);
        exit(EXIT_FAILURE);

    }

    printf("[Сервер запущен на %s:%d]\n", ip_addr, ntohs(server->server_addr.sin_port));
}

void udp_server_run(udp_server_t *server) {
    
    char response[1024];

    while (1) {
        
        if (udp_server_recv_message(server, response, sizeof(response)) < 0)
            continue;

        if (strcmp(response, "exit") == 0) {
            char client_ip[INET_ADDRSTRLEN];
            uint16_t client_port;
            get_client_ip(&server->client_addr, client_ip, sizeof(client_ip));
            get_client_port(&server->client_addr, &client_port);

            printf("[Клиент %s:%d]: отключился\n", client_ip, client_port);
            continue;
        }

        const char *modified_response = strupper(response);
        udp_server_send_message(server, modified_response);
    }
}

void udp_server_send_message(udp_server_t *server, const char *message) {
    
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", message);

    ssize_t sent = sendto(server->sockfd, buffer, strlen(buffer), 0,
                                (struct sockaddr*) &server->client_addr, 
                                sizeof(server->client_addr));

    if (sent < 0)
        perror("Ошибка: сообщение не отправлено.\n");
}

int udp_server_recv_message(udp_server_t *server, char *buffer, size_t buffer_size) {

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

void get_client_info(struct sockaddr_in *client_addr, char *client_ip, size_t ip_size, uint16_t *client_port) {
    inet_ntop(AF_INET, &client_addr->sin_addr, client_ip, ip_size);
    *client_port = ntohs(client_addr->sin_port);
}

void udp_server_destroy(udp_server_t *server) {
    close(server->sockfd);
}
