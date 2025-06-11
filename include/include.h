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

#define LOG_LEVEL(level, fmt, ...)                                                                 \
  do {                                                                                             \
    char buf[64];                                                                                  \
    time_t t = time(NULL);                                                                         \
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&t));                                \
    printf("[%s] [%s] %s:%d:%s(): " fmt, buf, level, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
  } while (0)

#define INFO(fmt, ...) LOG_LEVEL("INFO", fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) LOG_LEVEL("WARN", fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) LOG_LEVEL("ERROR", fmt, ##__VA_ARGS__)

#endif  // !_INCLUDE_H_
