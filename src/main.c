#include "../include/include.h"
#include "../include/server.h"

int main(int argc, char* argv[]) {
    server_t server;
    uint16_t port = PORT;

    INFO("Starting server\n");

    create_server(port, &server);

    start_server(&server);
}
