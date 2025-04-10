#include "udp_client.h"

int main(int argc, char* argv[]) {
    
    const char* server_ip = argv[1];
    u_int16_t server_port = atoi(argv[2]);
    
    udp_client_t client;
    udp_client_init(&client, server_ip, server_port);
    udp_client_run(&client);
    udp_client_destroy(&client);

    return 0;
}