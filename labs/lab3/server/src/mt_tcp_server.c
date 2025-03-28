#include "mt_tcp_server.h"
#include "str_utils.h"


void mt_tcp_server_init(mt_tcp_server *server) {

    if ((server->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка вызов 'socket()' прошел неудачно.");
        exit(EXIT_FAILURE);
    }

    memset(&server->server_addr, 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = 0;

    socklen_t server_addr_len = sizeof(server->server_addr);
    if (bind(server->sockfd, (struct sockaddr*)&server->server_addr, server_addr_len) == -1) {
        perror("Ошибка: вызов 'bind()' прошел не удачно.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    if (getsockname(server->sockfd, (struct sockaddr*)&server->server_addr, &server_addr_len) == -1) {
        perror("Ошибка: вызов 'bind()' прошел неудачно.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    printf("[Сервер запущен на %s:%d]\n", inet_ntoa(server->server_addr.sin_addr),
                                            ntohs(server->server_addr.sin_port));

    if (listen(server->sockfd, MAX_LISTEN_QUEUE) != 0) {
        perror("Ошибка: вызов 'listen()' прошел неудачно.");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }
}

void mt_tcp_server_run(mt_tcp_server *server) {

    while (1) {

        int connfd;
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        if ((connfd = accept(server->sockfd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0) {
            perror("Ошибка: вызов 'accept()' прошел неудачно.");
            continue;
        }

        pthread_t thread;
        pthread_attr_t thread_attr;
        pthread_attr_init(&thread_attr);
        pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

        int *connfd_ptr = &connfd;
        if (pthread_create(&thread, &thread_attr, (void*)client_handler, connfd_ptr) < 0) {
            perror("Ошибка: вызов 'pthread_create()' прошел неудачно.");
            close(connfd);
        }
        
        pthread_attr_destroy(&thread_attr);
    }
}

void *client_handler(void *arg) {
    
    int connfd = *((int*)arg);
    char response[1024];

    while (1) {

        if (mt_tcp_server_recvmsg(connfd, response, sizeof(response)) < 0) {
            break;
        }

        if (strcmp(response, "exit") == 0) {
            break;
        }

        char *modified_response = strupper(response);
        mt_tcp_server_sendmsg(connfd, modified_response);
    }

    close(connfd);
    pthread_exit(NULL);
}

int mt_tcp_server_recvmsg(int connfd, char *msg_buf, size_t buf_size) {

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if (getpeername(connfd, (struct sockaddr*)&client_addr, &client_addr_len) < 0) {
        perror("Ошибка: вызов функции 'getpeername()' прошел неудачно.");
        exit(EXIT_FAILURE);
    }

    ssize_t recvd_bytes = recv(connfd, msg_buf, buf_size, 0);

    if (recvd_bytes < 0) {
        perror("Ошибка: сообщение не получено.");
        return 1;
    }

    msg_buf[recvd_bytes] = '\0';
    printf("(Клиент %s:%d): %s\n", inet_ntoa(client_addr.sin_addr), 
                                    ntohs(client_addr.sin_port), msg_buf);
    return 0;
}

void mt_tcp_server_sendmsg(int connfd, char *msg_buf) {

    ssize_t sent_bytes = send(connfd, msg_buf, strlen(msg_buf), 0);

    if (sent_bytes < 0)
        perror("Ошибка: сообщение не отправлено.");
}

void mt_tcp_server_destroy(mt_tcp_server *server) {
    close(server->sockfd);
}