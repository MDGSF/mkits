#ifndef MKITS_MCKITS_CORE_MCKITS_MLOG_H_
#define MKITS_MCKITS_CORE_MCKITS_MLOG_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_LEVEL_Verbose 0
#define LOG_LEVEL_Debug 1
#define LOG_LEVEL_Info 2
#define LOG_LEVEL_Warning 3
#define LOG_LEVEL_Error 4
#define LOG_LEVEL_Fatal 5

extern int mckits_global_loglevel;

#define simple_log(level, ...)                                              \
  {                                                                         \
    if (mckits_global_loglevel <= level) {                                  \
      char str[4096];                                                       \
      snprintf(str, sizeof str, __VA_ARGS__);                               \
      fprintf(stderr, "[" #level "] %s:%d: %s\n", __FILE__, __LINE__, str); \
    }                                                                       \
  }

#define verbolog(...) \
  { simple_log(LOG_LEVEL_Verbose, __VA_ARGS__); }

#define dbglog(...) \
  { simple_log(LOG_LEVEL_Debug, __VA_ARGS__); }

#define infolog(...) \
  { simple_log(LOG_LEVEL_Info, __VA_ARGS__); }

#define warnlog(...) \
  { simple_log(LOG_LEVEL_Warning, __VA_ARGS__); }

#define errlog(...) \
  { simple_log(LOG_LEVEL_Error, __VA_ARGS__); }

#define fatallog(...) \
  { simple_log(LOG_LEVEL_Fatal, __VA_ARGS__); }

#ifdef __cplusplus
}
#endif

#endif
