#include "net/Epoll.h"

#include <sys/epoll.h>

#include <cstring>

#include "mckits/core/mckits_mlog.h"

Epoll::Epoll() {
  epfd_ = epoll_create(1);
  if (epfd_ == -1) {
    err_sys("epoll create failed");
  }
}

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
  int32_t event_flag = 0;

  auto iter = fd_event_flags_.find(fd);
  if (iter == fd_event_flags_.end()) {
    // 找不到
    event_flag = EPOLLIN;
    fd_event_flags_[fd] = event_flag;
  } else {
    // 找到了

    event_flag = iter->second;
    if (event_flag & EPOLLIN) {
      // 已经有 read 这个事件
      return;
    }

    event_flag |= EPOLLIN;
    fd_event_flags_[fd] = event_flag;
  }

  struct epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = event_flag;
  e.data.ptr = event_dispatcher;
  if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &e) < 0) {
    // TODO: err log
  }
}

void Epoll::register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                 bool write_event) {
  int32_t event_flag = 0;

  auto iter = fd_event_flags_.find(fd);
  if (iter == fd_event_flags_.end()) {
    // 找不到
    event_flag = EPOLLOUT;
    fd_event_flags_[fd] = event_flag;
  } else {
    // 找到了

    event_flag = iter->second;
    if (event_flag & EPOLLOUT) {
      // 已经有 read 这个事件
      return;
    }

    event_flag |= EPOLLOUT;
    fd_event_flags_[fd] = event_flag;
  }

  struct epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = event_flag;
  e.data.ptr = event_dispatcher;
  if (epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &e) < 0) {
    // TODO: err log
  }
}

void Epoll::unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                                  bool read_event) {
  int32_t event_flag = 0;
  int operation = 0;

  auto iter = fd_event_flags_.find(fd);
  if (iter == fd_event_flags_.end()) {
    return;
  } else {
    event_flag = iter->second;
    if (event_flag & EPOLLIN) {
      return;
    }

    event_flag &= ~EPOLLIN;
    if (event_flag == 0) {
      fd_event_flags_.erase(iter);
      operation = EPOLL_CTL_DEL;
    } else {
      fd_event_flags_[fd] = event_flag;
      operation = EPOLL_CTL_MOD;
    }
  }

  struct epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = event_flag;
  e.data.ptr = event_dispatcher;
  if (epoll_ctl(epfd_, operation, fd, &e) < 0) {
    // TODO: err log
  }
}

void Epoll::unregister_write_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool write_event) {
  int32_t event_flag = 0;
  int operation = 0;

  auto iter = fd_event_flags_.find(fd);
  if (iter == fd_event_flags_.end()) {
    return;
  } else {
    event_flag = iter->second;
    if (event_flag & EPOLLOUT) {
      return;
    }

    event_flag &= ~EPOLLOUT;

    if (event_flag == 0) {
      fd_event_flags_.erase(iter);
      operation = EPOLL_CTL_DEL;
    } else {
      fd_event_flags_[fd] = event_flag;
      operation = EPOLL_CTL_MOD;
    }
  }

  struct epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = event_flag;
  e.data.ptr = event_dispatcher;
  if (epoll_ctl(epfd_, operation, fd, &e) < 0) {
    // TODO: err log
  }
}

void Epoll::unregister_read_write_event(int fd,
                                        IEventDispatcher* event_dispatcher) {
  auto iter = fd_event_flags_.find(fd);
  if (iter == fd_event_flags_.end()) {
    return;
  } else {
    fd_event_flags_.erase(iter);
  }

  struct epoll_event e;
  memset(&e, 0, sizeof(e));
  e.events = 0;
  e.data.ptr = event_dispatcher;
  if (epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, &e) < 0) {
    // TODO: err log
  }
}
