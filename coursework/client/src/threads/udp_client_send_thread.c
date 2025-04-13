#include "udp_client.h"

void* udp_client_send_thread(void* arg) {

    udp_client_t* client = (udp_client_t*) arg;
    char message[1024];

    while (true) {

        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp("/quit", message) == 0) { 
            udp_client_send_msg(client, message);
            break;
        }

        udp_client_send_msg(client, message);
    }

    return NULL;
}
