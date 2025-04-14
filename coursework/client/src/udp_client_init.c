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

    
    printf("[Подключение к серверу %s:%d прошло успешно]\n", 
            server_addr, server_port);

    sem_init(&client->print_semaphore, 0, 1);

}
