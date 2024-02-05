// Inspired by skynet/socket_poll.h
#ifndef MKITS_INCLUDE_MCKITS_CORE_MCKITS_SOCKET_POLLER_H_
#define MKITS_INCLUDE_MCKITS_CORE_MCKITS_SOCKET_POLLER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int mckits_poller_fd;

struct MckitsPollerEvent {
  void* user_data;
  bool read;
  bool write;
  bool error;
  bool eof;
};

/*
@brief: Check whether fd is valid.
@return:
  true: means fd is valid.
  false: means fd is invalid.
*/
bool mckits_socket_poller_is_valid(mckits_poller_fd fd);

/*
@brief:
*/
mckits_poller_fd mckits_socket_poller_new();

/*
@brief:
*/
void mckits_socket_poller_drop(mckits_poller_fd fd);

/*
@brief:
*/
int mckits_socket_poller_add(mckits_poller_fd fd, int sock, void* user_data);

/*
@brief:
*/
void mckits_socket_poller_del(mckits_poller_fd fd, int sock);

/*
@brief:
*/
int mckits_socket_poller_enable(mckits_poller_fd fd, int sock, void* user_data,
                                bool read_enable, bool write_enable);

/*
@brief:
*/
int mckits_poller_poller_wait(mckits_poller_fd fd,
                              struct MckitsPollerEvent* event, int max_event);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_SOCKET_POLLER_H_
