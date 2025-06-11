#include "include.h"
#include "server.h"

int main(int argc, char *argv[]) {
  server_t server;
  uint16_t port = PORT;

  create_server(port, &server);

  start_server(&server);
}
