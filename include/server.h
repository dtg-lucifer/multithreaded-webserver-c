#ifndef _SERVER_H_
#define _SERVER_H_

#include "include.h"

/**
 * Renaming the big old `struct sockaddr`
 * to just `SA` for the sake of simplicity
 */
typedef struct sockaddr SA;

/**
 * Renaming the `struct sockaddr_in`
 * to just `SIN` for the sake of simplicity
 */
typedef struct sockaddr_in SIN;

/**
 * This is important to set the buffer size according to
 * the system the server is running on
 *
 * default value is 4096 bytes
 */
#define BUFFER_SIZE 4096

/**
 * Default port for the server
 */
#define PORT 8998

/**
 * server implementation to hold
 * the information about the server in a struct
 */
typedef struct {
  int sockfd;                  // File descriptor for the socket connection
  SIN addr;                    // socket address info
  socklen_t addr_len;          // Length of the address structure
  uint8_t buffer[BUFFER_SIZE]; // Buffer for incoming data (default 4096 bytes
                               // each consumes 8 bits)
} server_t;

// Global server declaration for signal handler
extern server_t *global_server;

/**
 * Creates a server socket and binds it to the specified port.
 *
 * @param port - port range for the server from 0 - 65535
 * @param *server - a pointer to a `server_t` struct
 */
void create_server(uint16_t port, server_t *server);

/**
 * Starts the server and listens for incoming connections.
 *
 * @param *server - a pointer to a `server_t` struct
 */
void start_server(server_t *server);

#endif // !_SERVER_H_
