#include "mckits/core/mckits_mlog.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MCKITS_LOG_MAX_LINE 4096

int mckits_global_loglevel = MKITS_LOG_LEVEL_ERROR;

void simple_log_impl(int log_level, const char* filename, int line,
                     const char* format, ...) {
  if (mckits_global_loglevel <= log_level ||
      log_level == MKITS_LOG_LEVEL_CRITICAL) {
    va_list ap;
    va_start(ap, format);

    char* p = strrchr(filename, '/');
    char buf[MCKITS_LOG_MAX_LINE] = {0};
    vsnprintf(buf, sizeof(buf), format, ap);
    fprintf(stderr, "[%s] %s:%d: %s\n", mckits_log_level_name[log_level],
            p ? p + 1 : filename, line, buf);

    va_end(ap);

    if (log_level == MKITS_LOG_LEVEL_FATAL) {
      abort();
    }
  }
}

static void err_doit(int show_errno, int log_level, const char* filename,
                     int line, const char* fmt, va_list ap) {
  int errno_save = errno;

  char buf[MCKITS_LOG_MAX_LINE] = {0};
  vsnprintf(buf, sizeof(buf), fmt, ap);
  size_t n = strlen(buf);

  if (show_errno) {
    snprintf(buf + n, sizeof(buf) - n, ": %s", strerror(errno_save));
  }

  fflush(stdout);  // in case stdout and stderr are the same

  char* p = strrchr(filename, '/');
  fprintf(stderr, "[%s] %s:%d: %s\n", mckits_log_level_name[log_level],
          p ? p + 1 : filename, line, buf);

  fflush(stderr);
}

void err_ret_impl(const char* filename, int line, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, MKITS_LOG_LEVEL_INFO, filename, line, fmt, ap);
  va_end(ap);
}

void err_sys_impl(const char* filename, int line, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, MKITS_LOG_LEVEL_ERROR, filename, line, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_dump_impl(const char* filename, int line, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, MKITS_LOG_LEVEL_ERROR, filename, line, fmt, ap);
  va_end(ap);
  abort();  // dump core and terminate
  // exit(1);  // shouldn't get here
}

void err_msg_impl(const char* filename, int line, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(0, MKITS_LOG_LEVEL_INFO, filename, line, fmt, ap);
  va_end(ap);
}

void err_quit_impl(const char* filename, int line, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  err_doit(0, MKITS_LOG_LEVEL_ERROR, filename, line, fmt, ap);
  va_end(ap);
  exit(1);
}
