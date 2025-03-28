#include "mp_tcp_server.h"

int main(int argc, char *argv[]) {

    mp_tcp_server server;
    mp_tcp_server_init(&server);
    mp_tcp_server_run(&server);
    mp_tcp_server_destroy(&server);
    return 0;
}