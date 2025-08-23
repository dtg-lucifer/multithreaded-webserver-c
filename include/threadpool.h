#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include "include.h"
#include "server.h"

#define MAX_QUEUE 128
#define NUM_THREADS 8

typedef struct {
  int client_socks[MAX_QUEUE];
  int front, rear;
  int count;
  int shutdown;

  pthread_mutex_t lock;
  pthread_cond_t has_jobs;

  pthread_t threads[NUM_THREADS];
  server_t *server; // Reference to server for buffer etc.
} threadpool_t;

void threadpool_init(threadpool_t *pool, server_t *server);
void threadpool_add_job(threadpool_t *pool, int client_sock);
void threadpool_shutdown(threadpool_t *pool);
void *worker_thread(void *arg);

#endif // !_THREADPOOL_H_
