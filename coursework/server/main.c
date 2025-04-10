#include "udp_server.h"

int main(int argc, char* argv[]) {

    udp_server_t server;
    udp_server_init(&server, argv[1]);
    udp_server_run(&server);
    udp_server_destroy(&server);
    return 0;
}