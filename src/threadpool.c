#include "threadpool.h"
#include "connection.h"

void *worker_thread(void *arg) {
  threadpool_t *pool = (threadpool_t *)arg;

  while (1) {
    pthread_mutex_lock(&pool->lock);

    while (pool->count == 0) {
      pthread_cond_wait(&pool->has_jobs, &pool->lock);
    }

    int client_sock = pool->client_socks[pool->front];
    pool->front = (pool->front + 1) % MAX_QUEUE;
    pool->count--;

    pthread_mutex_unlock(&pool->lock);

    // Handle the client
    if (handle_connection(pool->server, &client_sock) >= 0) {
      const char *resp = "HTTP/1.1 200 OK\r\n\r\nHello World!\r\n\r\n";
      send_data(pool->server, resp, strlen(resp), &client_sock);
    }

    close(client_sock);
  }

  return NULL;
}

void threadpool_init(threadpool_t *pool, server_t *server) {
  pool->front = 0;
  pool->rear = 0;
  pool->count = 0;
  pool->server = server;

  pthread_mutex_init(&pool->lock, NULL);
  pthread_cond_init(&pool->has_jobs, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&pool->threads[i], NULL, worker_thread, pool);
  }
}

void threadpool_add_job(threadpool_t *pool, int client_sock) {
  pthread_mutex_lock(&pool->lock);

  if (pool->count == MAX_QUEUE) {
    fprintf(stderr, "Job queue full, dropping client\n");
    close(client_sock);
  } else {
    pool->client_socks[pool->rear] = client_sock;
    pool->rear = (pool->rear + 1) % MAX_QUEUE;
    pool->count++;
    pthread_cond_signal(&pool->has_jobs);
  }

  pthread_mutex_unlock(&pool->lock);
}
