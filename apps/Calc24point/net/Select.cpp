#include "net/Select.h"

Select::Select() {}

Select::~Select() {}

void Select::poll(int timeout_us,
                  std::vector<IEventDispatcher*>& triggered_fds) {
  struct timeval tv;
  tv.tv_sec = timeout_us / 1000000;
  tv.tv_usec = timeout_us - timeout_us / 1000000 * 1000000;
  int n = ::select(maxfd_ + 1, &readfds_, &writefds_, &exceptsfds_, &tv);
  if (n == 0) {
    return;
  } else if (n < 0) {
    return;
  }

  // TODO
}

void Select::register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                 bool read_event) {
  if (maxfd_ < fd) {
    maxfd_ = fd;
  }

  FD_SET(fd, &readfds_);
}

void Select::register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                  bool write_event) {
  if (maxfd_ < fd) {
    maxfd_ = fd;
  }

  FD_SET(fd, &writefds_);
}

void Select::unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) {}

void Select::unregister_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) {}

void Select::unregister_read_write_event(int fd,
                                         IEventDispatcher* event_dispatcher) {}
