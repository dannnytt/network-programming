#include "udp_client.h"

void* udp_client_recv_thread(void *arg) {
    
    udp_client_t *client = (udp_client_t*) arg;
    char buffer[1024];


    while (true) {

        udp_client_recv_msg(client, buffer, sizeof(buffer));
        
        sem_wait(&client->print_semaphore);
        
        printf("\r(Другой клиент) > %s\n", buffer);
        printf("(Вы) > ");
        fflush(stdout);
        
        sem_post(&client->print_semaphore);
    }

    return NULL;
}
