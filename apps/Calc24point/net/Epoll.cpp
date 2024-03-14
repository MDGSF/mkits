#include "net/Epoll.h"

Epoll::Epoll() {}

Epoll::~Epoll() {}

void Epoll::poll(int timeout_us,
                 std::vector<IEventDispatcher*>& triggered_fds) {
  // epoll wait
  struct epoll_event events[1024];
  int timeout_ms = 500;
  bool enable_read = false;
  bool enable_write = false;
  int n = epoll_wait(epfd_, events, 1024, timeout_ms);
  for (int i = 0; i < n; ++i) {
    if (events[i].events & EPOLLIN) {
      enable_read = true;
    } else {
      enable_read = false;
    }
    if (events[i].events & EPOLLOUT) {
      enable_write = true;
    } else {
      enable_write = false;
    }
    IEventDispatcher* event_dispatcher = (IEventDispatcher*)events[i].data.ptr;
    event_dispatcher->enable_read(enable_read);
    event_dispatcher->enable_write(enable_write);
    triggered_fds.push_back(event_dispatcher);
  }
}

void Epoll::register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                bool read_event) {
  struct epoll_event e;
  e.events |= EPOLLIN;
  e.data.ptr = event_dispatcher;
}

void Epoll::register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                 bool write_event) {
  struct epoll_event e;
  e.events |= EPOLLOUT;
  e.data.ptr = event_dispatcher;
}
