#include "tcp_client.h"

int main(int argc, char *argv[]) {

    tcp_client client;
    tcp_client_init(&client, argv[1], atoi(argv[2]));
    tcp_client_run(&client);
    tcp_client_destroy(&client);

    return 0;
}