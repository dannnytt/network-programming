#include "udp_client.h"

void udp_client_run(udp_client_t *client) {
    
    char message[1024], response[1024];

    while (true) {

        printf("(Клиент): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp("exit", message) == 0) { 
            udp_client_send_msg(client, message);
            break;
        }

        udp_client_send_msg(client, message);
        udp_client_recv_msg(client, response, sizeof(response));
    }
}
