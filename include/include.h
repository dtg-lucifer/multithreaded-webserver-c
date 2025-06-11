#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LOG(fmt, ...)                                                 \
  do {                                                                \
    time_t now = time(NULL);                                          \
    char buf[26];                                                     \
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
    printf("[%s] " fmt, buf, ##__VA_ARGS__);                          \
  } while (0)

#define LOG_ERR(fmt, ...)                                             \
  do {                                                                \
    time_t now = time(NULL);                                          \
    char buf[26];                                                     \
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now)); \
    fprintf(stderr, "[%s] " fmt, buf, ##__VA_ARGS__);                 \
  } while (0)

#endif  // !_INCLUDE_H_
