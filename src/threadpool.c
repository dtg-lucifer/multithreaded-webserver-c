#include "../include/threadpool.h"

#include "../include/connection.h"
#include "../include/include.h"  // Make sure include.h is included for LOG macro

void* worker_thread(void* arg) {
  threadpool_t* pool = (threadpool_t*)arg;

  LOG("[THREAD %lu] Started\n", pthread_self());

  while (1) {
    pthread_mutex_lock(&pool->lock);

    // Check shutdown flag before waiting
    while (pool->count == 0 && !pool->shutdown) {
      pthread_cond_wait(&pool->has_jobs, &pool->lock);
    }

    if (pool->shutdown) {
      pthread_mutex_unlock(&pool->lock);
      LOG("[THREAD %lu] Shutting down\n", pthread_self());
      break;
    }

    int client_sock = pool->client_socks[pool->front];
    pool->front = (pool->front + 1) % MAX_QUEUE;
    pool->count--;

    LOG("[THREAD %lu] Picked up job\n", pthread_self());

    pthread_mutex_unlock(&pool->lock);

    // Handle the client
    if (handle_connection(pool->server, &client_sock) >= 0) {
      const char* resp = "HTTP/1.1 200 OK\r\n\r\nHello World!\r\n\r\n";
      send_data(pool->server, resp, strlen(resp), &client_sock);
    }

    LOG("[THREAD %lu] Finished job\n", pthread_self());
    close(client_sock);
  }

  return NULL;
}

void threadpool_init(threadpool_t* pool, server_t* server) {
  pool->front = 0;
  pool->rear = 0;
  pool->count = 0;
  pool->shutdown = 0;
  pool->server = server;

  pthread_mutex_init(&pool->lock, NULL);
  pthread_cond_init(&pool->has_jobs, NULL);

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&pool->threads[i], NULL, worker_thread, pool);
  }
}

void threadpool_shutdown(threadpool_t* pool) {
  pthread_mutex_lock(&pool->lock);
  pool->shutdown = 1;
  pthread_cond_broadcast(&pool->has_jobs);
  pthread_mutex_unlock(&pool->lock);

  for (int i = 0; i < NUM_THREADS; ++i) {
    pthread_join(pool->threads[i], NULL);
    LOG("[THREADPOOL] Thread %d joined\n", i);
  }

  pthread_mutex_destroy(&pool->lock);
  pthread_cond_destroy(&pool->has_jobs);

  LOG("[THREADPOOL] Shutdown complete.\n");
}

void threadpool_add_job(threadpool_t* pool, int client_sock) {
  pthread_mutex_lock(&pool->lock);

  if (pool->count == MAX_QUEUE) {
    LOG_ERR("Job queue full, dropping client\n");
    close(client_sock);
  } else {
    pool->client_socks[pool->rear] = client_sock;
    pool->rear = (pool->rear + 1) % MAX_QUEUE;
    pool->count++;
    pthread_cond_signal(&pool->has_jobs);
  }

  pthread_mutex_unlock(&pool->lock);
}
