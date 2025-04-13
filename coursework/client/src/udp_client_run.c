#include "udp_client.h"

void udp_client_run(udp_client_t *client) {
    
    pthread_t recv_thread, send_thread;
    
    pthread_create(&recv_thread, NULL, udp_client_recv_thread, (void*)client);
    pthread_create(&send_thread, NULL, udp_client_send_thread, (void*)client);

    pthread_join(send_thread, NULL);
    pthread_cancel(recv_thread);
    pthread_join(recv_thread, NULL);
}
