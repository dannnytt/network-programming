#include "udp_client.h"

void udp_client_destroy(udp_client_t *client) {
    close(client->sockfd);
    sem_destroy(&client->print_semaphore);
}
