#include "tcp_client.h"

void tcp_client_init(tcp_client *client, char *server_ip, uint16_t server_port) {

    if ((client->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка: вызов 'socket()' прошел неудачно.");
        exit(EXIT_FAILURE);
    }

    memset(&client->client_addr, 0, sizeof(client->client_addr));
    client->client_addr.sin_family = AF_INET;
    client->client_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &client->client_addr.sin_addr) != 1) {
        perror("Ошибка: вызов 'inet_pton()' прошел неудачно.");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    if (connect(client->sockfd, (struct sockaddr*)&client->client_addr, sizeof(client->client_addr)) < 0) {
        perror("Ошибка: вызов 'connect()' прошел неудачно.");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in local_addr;
    socklen_t local_addr_len = sizeof(local_addr);
    if (getsockname(client->sockfd, (struct sockaddr*)&local_addr, &local_addr_len) != 0) {
        perror("Ошибка: вызов 'getsockname()' прошел неудачно.");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in remote_addr;
    socklen_t remote_addr_len = sizeof(remote_addr);
    if (getpeername(client->sockfd, (struct sockaddr*)&remote_addr, &remote_addr_len) < 0) {
        perror("Ошибка: вызов 'getpeername()' прошел неудачно.");
        close(client->sockfd);
        exit(EXIT_FAILURE);
    }

    inet_ntop(AF_INET, &local_addr.sin_addr, client->client_ip, INET_ADDRSTRLEN);
    client->client_port = ntohs(local_addr.sin_port);

    inet_ntop(AF_INET, &remote_addr.sin_addr, client->server_ip, INET_ADDRSTRLEN);
    client->server_port = ntohs(remote_addr.sin_port);
}

void tcp_client_run(tcp_client *client) {

    char message[1024], response[1024];

    while (1) {
        
        printf("(Клиент %s:%d): ", client->client_ip, client->client_port);
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            tcp_client_sendmsg(client, message);
            break;
        }

        tcp_client_sendmsg(client, message);
        tcp_client_recvmsg(client, response, sizeof(response));
    }

}

void tcp_client_sendmsg(tcp_client *client, char *msg_buf) {

    ssize_t sent_bytes = send(client->sockfd, msg_buf, strlen(msg_buf), 0);
}

void tcp_client_recvmsg(tcp_client *client, char *msg_buf, size_t buf_size) {

    ssize_t recvd_bytes = recv(client->sockfd, msg_buf, buf_size - 1, 0);

    if (recvd_bytes < 0) {
        perror("Ошибка: сообщение не получено.");
        return;
    }

    msg_buf[recvd_bytes] = '\0';
    printf("(Сервер %s:%d): %s\n", client->server_ip, client->server_port, msg_buf);
}

void tcp_client_destroy(tcp_client *client) {
    close(client->sockfd);
}