#include "../include/server.h"

#include "../include/connection.h"
#include "../include/include.h"
#include "../include/threadpool.h"

// Threadpool variable
threadpool_t pool;

// Global variable to store server reference
server_t* global_server = NULL;

/**
 * Creates a server socket and binds it to the specified port.
 *
 * @param port - port range for the server from 0 - 65535
 * @param *server - a pointer to a `server_t` struct
 */
void create_server(uint16_t port, server_t* server) {
    // Storing the size of the address structure
    server->addr_len = sizeof(server->addr);

    // Create a socket
    server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->sockfd < 0) {
        perror("Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    // Set socket option to reuse address
    int opt = 1;
    if (setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Failed to set SO_REUSEADDR option");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    // Set up the address structure
    memset(&server->addr, 0, server->addr_len);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,          // Use IPv4 addresses
        .sin_addr.s_addr = INADDR_ANY,  // Bind to all interfaces
        .sin_port = htons(port)         // Convert port to network byte order
    };

    memcpy(&server->addr, &addr,
           sizeof(addr));  // Copy the address to the server struct

    // Bind the socket to the address and port
    if (bind(server->sockfd, (SA*)&server->addr, sizeof(server->addr)) < 0) {
        perror("Failed to bind socket");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }
}

/**
 * To help gracefully shutdown the server and the threadpool
 */
void handle_sigint(int sig) {
    WARN("\n[SERVER] Caught signal %d. Shutting down...\n", sig);

    // Close the server socket to unblock accept()
    if (global_server) {
        close(global_server->sockfd);
    }

    threadpool_shutdown(&pool);
    WARN("[SERVER] Shutdown completed successfully.\n");
    exit(0);
}

/**
 * Starts the server and listens for incoming connections.
 *
 * @param *server - a pointer to a `server_t` struct
 */
void start_server(server_t* server) {
    // Set global server reference for signal handler
    global_server = server;

    signal(SIGINT, handle_sigint);

    // Start listening for incoming connections
    if (listen(server->sockfd, 10) < 0) {
        perror("Failed to listen on socket");
        close(server->sockfd);
        exit(EXIT_FAILURE);
    }

    INFO("Server is listening on port %d\n", ntohs(server->addr.sin_port));

    threadpool_init(&pool, server);

    // Accept incoming connections (this is a blocking call)
    while (1) {
        // Accept the connection
        int client_sock = accept_connection(server);

        if (client_sock > 0) {
            threadpool_add_job(&pool, client_sock);
        }
    }
}
