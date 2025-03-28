#include "mt_tcp_server.h"

int main(int argc, char *argv[]) {

    mt_tcp_server server;
    mt_tcp_server_init(&server);
    mt_tcp_server_run(&server);
    mt_tcp_server_destroy(&server);

    return 0;
}