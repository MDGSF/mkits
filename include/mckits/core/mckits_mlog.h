#ifndef MKITS_INCLUDE_MCKITS_CORE_MCKITS_MLOG_H_
#define MKITS_INCLUDE_MCKITS_CORE_MCKITS_MLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_LEVEL_VERBOSE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_FATAL 5

static const char mckits_log_level_name[][5] = {
    "Verb", "Debu", "Info", "Warn", "Erro", "Fata",
};

extern int mckits_global_loglevel;

void simple_log_impl(int log_level, const char* filename, int line,
                     const char* format, ...);

#define verbolog(...) \
  simple_log_impl(LOG_LEVEL_VERBOSE, __FILE__, __LINE__, __VA_ARGS__)
#define dbglog(...) \
  simple_log_impl(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define infolog(...) \
  simple_log_impl(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define warnlog(...) \
  simple_log_impl(LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define errlog(...) \
  simple_log_impl(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define fatallog(...) \
  simple_log_impl(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)

// show filename, line, errno, msg
void err_ret_impl(const char* filename, int line, const char* fmt, ...);

// show filename, line, errno, msg, exit(1)
void err_sys_impl(const char* filename, int line, const char* fmt, ...);

// show filename, line, errno, msg, abort()
void err_dump_impl(const char* filename, int line, const char* fmt, ...);

// show filename, line, msg
void err_msg_impl(const char* filename, int line, const char* fmt, ...);

// show filename, line, msg, exit(1)
void err_quit_impl(const char* filename, int line, const char* fmt, ...);

#define err_ret(...) err_ret_impl(__FILE__, __LINE__, __VA_ARGS__)
#define err_sys(...) err_sys_impl(__FILE__, __LINE__, __VA_ARGS__)
#define err_dump(...) err_dump_impl(__FILE__, __LINE__, __VA_ARGS__)
#define err_msg(...) err_msg_impl(__FILE__, __LINE__, __VA_ARGS__)
#define err_quit(...) err_quit_impl(__FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_MLOG_H_
