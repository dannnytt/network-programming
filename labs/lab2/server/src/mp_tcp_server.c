#include "mp_tcp_server.h"
#include "zombie_reaper.h"
#include "strupper.h"

void mp_tcp_server_init(mp_tcp_server *server) {
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->sockfd < 0) {
        perror("Ошибка: вызов 'socket()' не удался.");
        exit(EXIT_FAILURE);
    }

    memset(&server->server_addr, 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = 0;

    socklen_t server_addr_len = sizeof(server->server_addr);
    if (bind(server->sockfd, (struct sockaddr*) &server->server_addr, server_addr_len) != 0) {
        perror("Ошибка: вызов 'bind()' не удался.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }


    if (getsockname(server->sockfd, (struct sockaddr*) &server->server_addr, &server_addr_len) != 0) {
        perror("Ошибка: вызов 'getsockname()' не удался.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    printf("[Сервер запущен на %s:%d]\n", inet_ntoa(server->server_addr.sin_addr),
                                            ntohs(server->server_addr.sin_port));

    if (listen(server->sockfd, MAX_LISTEN_QUEUE) != 0) {
        perror("Ошибка: вызов 'listen()' не удался.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }
}

void mp_tcp_server_run(mp_tcp_server *server) {
    signal(SIGCHLD, zombie_process_reaper);
    while (1) {

        int connfd;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        if ((connfd = accept(server->sockfd, (struct sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("Ошибка: вызов 'accept()' не удался.");
            continue;
        }


        switch(fork()) {

            case -1:
                perror("Ошибка: вызов 'fork()' прошел неуспешно.");
                break;

            case 0:
                close(server->sockfd);

                mp_tcp_server_handle_client(connfd);

                close(connfd);
                exit(EXIT_SUCCESS);
                break;

            default:
                close(connfd);
        }
    }
}

void mp_tcp_server_handle_client(int connfd) {

    char response[1024];
    while (1) {

        if ((mp_tcp_server_recvmsg(connfd, response, sizeof(response))) < 0)
            continue;

        if (strcmp(response, "exit") == 0) {
            close(connfd);
            exit(EXIT_SUCCESS);
        }

        const char *modified_response = strupper(response);
        mp_tcp_server_sendmsg(connfd, modified_response);

    }
}

int mp_tcp_server_recvmsg(int connfd, char *msg_buf, size_t buf_size) {

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if ((getpeername(connfd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
        perror("Ошибка: вызов функции 'getpeername()' прошел неудачно.");
        exit(EXIT_FAILURE);
    }

    ssize_t recvd_bytes = recv(connfd, msg_buf, buf_size - 1, 0);
    if (recvd_bytes < 0) {
        perror("Ошибка: сообщение не получено.");
        return 1;
    }

    msg_buf[recvd_bytes] = '\0';
    printf("(Клиент %s:%d): %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), msg_buf);
    return 0;
}

void mp_tcp_server_sendmsg(int connfd, const char *msg_buf) {

    ssize_t sent_bytes = send(connfd, msg_buf, strlen(msg_buf), 0);

    if (sent_bytes < 0)
        perror("Ошибка: сообщение не отправлено.");
}

void mp_tcp_server_destroy(mp_tcp_server *server) {
    close(server->sockfd);
}