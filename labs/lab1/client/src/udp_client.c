#include "udp_client.h"

void udp_client_init(udp_client_t *client, const char *server_addr, uint16_t server_port) {

    client->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client->sockfd < 0) {
        perror("Ошибка: сокет клиента не создан.\n");
        exit(EXIT_FAILURE);
    }

    memset(&client->server_addr, 0, sizeof(client->server_addr));
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(server_port);
    
    
    if (inet_pton(AF_INET, server_addr, &client->server_addr.sin_addr) != 1) {
        perror("Ошибка: ip-адрес сервера не преобразован.\n");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    client->server_addr_len = sizeof(client->server_addr);
    
    printf("[Подключение к серверу %s:%d прошло успешно]\n", 
            server_addr, server_port);
}

void udp_client_run(udp_client_t *client) {
    
    char message[1024], response[1024];

    while (true) {

        printf("(Клиент): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp("exit", message) == 0) { 
            udp_client_send_message(client, message);
            break;
        }

        udp_client_send_message(client, message);
        udp_client_recv_message(client, response, sizeof(response));
    }
}

void udp_client_send_message(udp_client_t *client, const char* message) {
    
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s", message);

    ssize_t sent_bytes = sendto(client->sockfd, buffer, strlen(buffer), 0, 
                                (struct sockaddr*) &client->server_addr, 
                                client->server_addr_len);
    
    if (sent_bytes < 0)
        perror("Ошибка: сообщение не отправлено.\n");

}

void udp_client_recv_message(udp_client_t *client, char *buffer, size_t buffer_size) {
    
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

void udp_client_destroy(udp_client_t *client) {
    close(client->sockfd);
}
