#ifndef UTILS_H_
#define UTILS_H_

#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LEVEL_ERROR 0x00
#define LEVEL_WARN 0x01
#define LEVEL_INFO 0x02
#define LEVEL_DEBUG 0x03

#define ERROR_TAG "ERROR"
#define WARN_TAG "WARN"
#define INFO_TAG "INFO"
#define DEBUG_TAG "DEBUG"

#ifndef LOG_LEVEL
#define LOG_LEVEL LEVEL_INFO
#endif

/* The LOGx macros and the redirected LOG_PRINT use only C99 variadic macros.
 * Some compilers (Renesas CC-RX) drop the comma of `, ##__VA_ARGS__` even
 * when arguments are present. */
#if LOG_REDIRECT
void peer_log(char *level_tag, const char *file_name, int line_number,
              const char *fmt, ...);
#define LOG_PRINT(level_tag, ...)                                              \
  peer_log(level_tag, __FILE__, __LINE__, __VA_ARGS__)
#else
#define LOG_PRINT(level_tag, fmt, ...)                                         \
  fprintf(stderr, "%s\t%s\t%d\t" fmt "\n", level_tag, __FILE__,                \
          __LINE__, ##__VA_ARGS__)
#endif

#if LOG_LEVEL >= LEVEL_DEBUG
#define LOGD(...) LOG_PRINT(DEBUG_TAG, __VA_ARGS__)
#else
#define LOGD(...)
#endif

#if LOG_LEVEL >= LEVEL_INFO
#define LOGI(...) LOG_PRINT(INFO_TAG, __VA_ARGS__)
#else
#define LOGI(...)
#endif

#if LOG_LEVEL >= LEVEL_WARN
#define LOGW(...) LOG_PRINT(WARN_TAG, __VA_ARGS__)
#else
#define LOGW(...)
#endif

#if LOG_LEVEL >= LEVEL_ERROR
#define LOGE(...) LOG_PRINT(ERROR_TAG, __VA_ARGS__)
#else
#define LOGE(...)
#endif

#define ALIGN32(num) ((num + 3) & ~3)

int utils_random_bytes(void *out, size_t size);
int utils_random_string(char *s, const int len);

int utils_get_hmac_sha1(const char *input, size_t input_len, const char *key,
                        size_t key_len, unsigned char *output);

#endif // UTILS_H_
