#include <udp_server.h>

void udp_server_sendto(udp_server_t *server, 
    const struct sockaddr_in *client_addr, 
    const struct sockaddr_in *sender_addr, 
    const char *msg)
{
    if (memcmp(client_addr, sender_addr, sizeof(struct sockaddr_in)) != 0) {
        sendto(
            server->sockfd,
            msg,
            strlen(msg),
            0,
            (struct sockaddr*)client_addr,
            sizeof(*client_addr)
        );
    }
}
