#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "include.h"
#include "server.h"

/**
 * Accepts a connection from a client and returns the client socket file
 * descriptor.
 *
 * @param server_p - a pointer to a `server_t` struct
 * @return int - the client socket file descriptor, or -1 on failure
 */
int accept_connection(server_t *server_p);

/**
 * Handles a connection from a client by accepting it and processing the data.
 *
 * @param server_p - a pointer to a `server_t` struct
 * @param client_socket_p - a pointer to an integer that will hold the client
 * socket file descriptor
 */
int handle_connection(server_t *server_p, int *client_socket_p);

/**
 * Receives data from a client and stores it in the server's buffer.
 *
 * @param server_p - a pointer to a `server_t` struct
 * @return size_t - the number of bytes received, or -1 on failure
 */
size_t receive_data(server_t *server_p);

/**
 * Sends data to a client.
 *
 * @param server_p - a pointer to a `server_t` struct
 * @param data - the data to send (in bytes array format)
 * @param length - the length of the data to send
 * @return ssize_t - the number of bytes sent, or -1 on failure
 */
size_t send_data(server_t *server_p, const char *data, size_t length,
                 int *client_sock);

#endif // !_CONNECTION_H_
