#include "../include/connection.h"

#include "../include/include.h"
#include "../include/server.h"

int accept_connection(server_t* server_p) {
  if (!server_p) {
    LOG_ERR("Server pointer is NULL\n");
    return -1;
  }

  SIN client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  int client_sock = accept(server_p->sockfd, (SA*)&client_addr, &client_addr_len);
  if (client_sock < 0) {
    LOG_ERR("Cannot accept the socket connection\n");
    return -1;
  }

  char client_ip[INET_ADDRSTRLEN];  // Allocate buffer for client IP Address
  inet_ntop(client_addr.sin_family, &client_addr.sin_addr, client_ip,
            INET_ADDRSTRLEN);  // Convert IP address to string

  LOG("Accepted connection from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

  return client_sock;
}

int handle_connection(server_t* server_p, int* client_sock) {
  if (!server_p || !client_sock) {
    LOG_ERR("Invalid arguments to handle_connection\n");
    return -1;
  }

  // Clear the buffer before reading
  memset(server_p->buffer, 0, BUFFER_SIZE);

  // Read one message from the client
  ssize_t bytes_read = recv(*client_sock, server_p->buffer, BUFFER_SIZE - 1, 0);
  if (bytes_read <= 0) {
    perror("Failed to read from client");
    close(*client_sock);
    return -1;
  }

  // Ensure null-termination
  server_p->buffer[bytes_read] = '\0';

  // Strip newline if present
  if (server_p->buffer[bytes_read - 1] == '\n') {
    server_p->buffer[bytes_read - 1] = '\0';
  }

  LOG("[CLIENT %d] Received data: %s\n", *client_sock, server_p->buffer);
  LOG("[CLIENT %d] Bytes read: %zd\n", *client_sock, bytes_read);

  return 1;
}

size_t send_data(server_t* server_p, const char* data, size_t length, int* client_sock) {
  ssize_t sent_bytes = send(*client_sock, data, length, 0);
  if (sent_bytes < 0) {
    perror("Failed to send response to client");
    close(*client_sock);
    return -1;
  }

  return sent_bytes;
}
