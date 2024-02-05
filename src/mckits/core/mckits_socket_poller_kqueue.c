#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

bool mckits_socket_poller_is_valid(mckits_poller_fd fd) { return fd != -1; }

mckits_poller_fd mckits_socket_poller_new() { return kqueue(); }

void mckits_socket_poller_drop(mckits_poller_fd fd) { close(fd); }

void mckits_socket_poller_del(mckits_poller_fd fd, int sock) {
  struct kevent ke;
  EV_SET(&ke, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
  kevent(fd, &ke, 1, NULL, 0, NULL);
  EV_SET(&ke, sock, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
  kevent(fd, &ke, 1, NULL, 0, NULL);
}

int mckits_socket_poller_add(mckits_poller_fd fd, int sock, void* user_data) {
  struct kevent ke;
  EV_SET(&ke, sock, EVFILT_READ, EV_ADD, 0, 0, user_data);
  if (kevent(fd, &ke, 1, NULL, 0, NULL) == -1 || ke.flags & EV_ERROR) {
    return -1;
  }
  EV_SET(&ke, sock, EVFILT_WRITE, EV_ADD, 0, 0, user_data);
  if (kevent(fd, &ke, 1, NULL, 0, NULL) == -1 || ke.flags & EV_ERROR) {
    EV_SET(&ke, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    kevent(fd, &ke, 1, NULL, 0, NULL);
    return -1;
  }
  EV_SET(&ke, sock, EVFILT_WRITE, EV_DISABLE, 0, 0, user_data);
  if (kevent(fd, &ke, 1, NULL, 0, NULL) == -1 || ke.flags & EV_ERROR) {
    mckits_socket_poller_del(fd, sock);
    return -1;
  }
  return 0;
}

int mckits_socket_poller_enable(mckits_poller_fd fd, int sock, void* user_data,
                                bool read_enable, bool write_enable) {
  int ret = 0;
  struct kevent ke;
  EV_SET(&ke, sock, EVFILT_READ, read_enable ? EV_ENABLE : EV_DISABLE, 0, 0,
         user_data);
  if (kevent(fd, &ke, 1, NULL, 0, NULL) == -1 || ke.flags & EV_ERROR) {
    ret |= 1;
  }
  EV_SET(&ke, sock, EVFILT_WRITE, write_enable ? EV_ENABLE : EV_DISABLE, 0, 0,
         user_data);
  if (kevent(fd, &ke, 1, NULL, 0, NULL) == -1 || ke.flags & EV_ERROR) {
    ret |= 1;
  }
  return ret;
}

int mckits_poller_poller_wait(mckits_poller_fd fd,
                              struct MckitsPollerEvent* event, int max_event) {
  struct kevent ev[max_event];
  int n = kevent(fd, NULL, 0, ev, max_event, NULL);

  for (int i = 0; i < n; i++) {
    e[i].s = ev[i].udata;
    unsigned filter = ev[i].filter;
    bool eof = (ev[i].flags & EV_EOF) != 0;
    e[i].write = (filter == EVFILT_WRITE) && (!eof);
    e[i].read = (filter == EVFILT_READ);
    e[i].error = (ev[i].flags & EV_ERROR) != 0;
    e[i].eof = eof;
  }

  return n;
}
