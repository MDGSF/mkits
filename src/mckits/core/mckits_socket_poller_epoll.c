#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

bool mckits_socket_poller_is_valid(mckits_poller_fd fd) { return fd != -1; }

mckits_poller_fd mckits_socket_poller_new() { return epoll_create(1024); }

void mckits_socket_poller_drop(mckits_poller_fd fd) { close(fd); }

int mckits_socket_poller_add(mckits_poller_fd fd, int sock, void* user_data) {
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.ptr = user_data;
  if (epoll_ctl(fd, EPOLL_CTL_ADD, sock, &ev) == -1) {
    return -1;
  }
  return 0;
}

void mckits_socket_poller_del(mckits_poller_fd fd, int sock) {
  epoll_ctl(fd, EPOLL_CTL_DEL, sock, NULL);
}

int mckits_socket_poller_enable(mckits_poller_fd fd, int sock, void* user_data,
                                bool read_enable, bool write_enable) {
  struct epoll_event ev;
  ev.events = (read_enable ? EPOLLIN : 0) | (write_enable ? EPOLLOUT : 0);
  ev.data.ptr = user_data;
  if (epoll_ctl(fd, EPOLL_CTL_MOD, sock, &ev) == -1) {
    return -1;
  }
  return 0;
}

int mckits_poller_poller_wait(mckits_poller_fd fd,
                              struct MckitsPollerEvent* event, int max_event) {
  struct epoll_event ev[max_event];
  int n = epoll_wait(fd, ev, max_event, -1);
  for (int i = 0; i < n; ++i) {
    event[i].user_data = ev[i].data.ptr;
    uint32_t flag = ev[i].events;
    event[i].write = (flag & EPOLLOUT) != 0;
    event[i].read = (flag & EPOLLIN) != 0;
    event[i].error = (flag & EPOLLERR) != 0;
    event[i].eof = (flag & EPOLLHUP) != 0;
  }
  return n;
}
