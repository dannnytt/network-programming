#include "udp_server.h"

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
