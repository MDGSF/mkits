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
@brief: Create a new poller.
@return: new poller file descriptor.
*/
mckits_poller_fd mckits_socket_poller_new();

/*
@brief: Drop the poller.
*/
void mckits_socket_poller_drop(mckits_poller_fd fd);

/*
@brief: Add a socket to poller.
@param fd[in]: poller file descriptor.
@param sock[in]: socket file descriptor.
@param user_data[in]: user data bind to `sock` file descriptor.
@return:
  On success, 0 is returned.
  On error, -1 is returned.
*/
int mckits_socket_poller_add(mckits_poller_fd fd, int sock, void* user_data);

/*
@brief: Delete a socket from poller.
@param fd[in]: poller file descriptor.
@param sock[in]: socket file descriptor.
*/
void mckits_socket_poller_del(mckits_poller_fd fd, int sock);

/*
@brief: Modify socket event.
@param fd[in]: poller file descriptor.
@param sock[in]: socket file descriptor.
@param user_data[in]: user data bind to `sock` file descriptor.
@param read_enable[in]: enable or disable read event.
@param write_enable[in]: enable or disable write event.
@return:
  On success, 0 is returned.
  On error, -1 is returned.
*/
int mckits_socket_poller_enable(mckits_poller_fd fd, int sock, void* user_data,
                                bool read_enable, bool write_enable);

/*
@brief: Wait events from poller.
@param fd[in]: poller file descriptor.
@param event[out]: Output events array.
@param max_event[in]: `event` array size. Means wants max event from poller.
@return: The number of events returned from poller.
  Smaller or equal to `max_event`.
*/
int mckits_poller_poller_wait(mckits_poller_fd fd,
                              struct MckitsPollerEvent* event, int max_event);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_SOCKET_POLLER_H_
