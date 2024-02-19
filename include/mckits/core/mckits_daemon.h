#ifndef MKITS_INCLUDE_MCKITS_CORE_MCKITS_DAEMON_H_
#define MKITS_INCLUDE_MCKITS_CORE_MCKITS_DAEMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Daemonize current process. Create pidfile, and lock pidfile.
@return:
  On success, 0 is returned.
  On error, -1 is returned.
*/
int mckits_daemon_init(const char* pidfile);

/*
@brief: Unlink pidfile.
@return:
  On success, 0 is returned.
  On error, -1 is returned.
*/
int mckits_daemon_exit(const char* pidfile);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_DAEMON_H_
