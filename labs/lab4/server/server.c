#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <arpa/inet.h>  
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/select.h> 
#include <errno.h>      

#define BUFLEN 512 

int main()
{
    int listen_sock, new_sock, max_fd, i;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    fd_set master_set, read_fds;
    char buffer[BUFLEN];
    int nbytes;

    if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // разрешаем переиспользование адреса
    int yes = 1;
    if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(0);          

    if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    addr_len = sizeof(server_addr);
    if (getsockname(listen_sock, (struct sockaddr *)&server_addr, &addr_len) < 0) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }
    printf("Server running on port %d\n", ntohs(server_addr.sin_port));

    if (listen(listen_sock, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // добавляем слушающий сокет.
    FD_ZERO(&master_set);
    FD_SET(listen_sock, &master_set);
    max_fd = listen_sock;

    // ждем событий на сокетах с помощью select.
    while (1) {
        read_fds = master_set;
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // проходим по всем дескрипторам от 0 до max_fd.
        for (i = 0; i <= max_fd; i++) {
            if (FD_ISSET(i, &read_fds)) {
                // событие на слушающем сокете – новое подключение
                if (i == listen_sock) {
                    addr_len = sizeof(client_addr);
                    new_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &addr_len);
                    if (new_sock < 0) {
                        perror("accept");
                    }
                    
                    else {
                        FD_SET(new_sock, &master_set); // добавляем новый сокет
                        if (new_sock > max_fd) {
                            max_fd = new_sock;
                        }
                        char client_ip[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
                        printf("New connection from %s:%d, socket %d\n", client_ip, ntohs(client_addr.sin_port), new_sock);
                    }
                }
                else {
                    // если событие уже установленном соединении – получаем данные.
                    nbytes = recv(i, buffer, BUFLEN - 1, 0);
                    if (nbytes <= 0) {
                        if (nbytes == 0) {
                            printf("Socket %d hung up\n", i);
                        }
                        else {
                            perror("recv");
                        }
                        close(i);
                        FD_CLR(i, &master_set);
                    }
                    else {
                        buffer[nbytes] = '\0'; // завершаем строку
                        // получаем адрес удаленного узла
                        struct sockaddr_in peer;
                        socklen_t peer_len = sizeof(peer);
                        if (getpeername(i, (struct sockaddr *)&peer, &peer_len) == 0) {
                            char peer_ip[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET, &peer.sin_addr, peer_ip, sizeof(peer_ip));
                            printf("Received from %s:%d: %s\n", peer_ip, ntohs(peer.sin_port), buffer);
                        }
                        else {
                            printf("Received from socket %d: %s\n", i, buffer);
                        }
                    }
                }
            }
        }
    }

    close(listen_sock);
    return 0;
}
