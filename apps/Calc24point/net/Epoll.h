#ifndef MKITS_APPS_CALC24POINT_NET_EPOLL_H_
#define MKITS_APPS_CALC24POINT_NET_EPOLL_H_

#include <sys/epoll.h>
#include <unistd.h>

#include <map>
#include <vector>

#include "net/IOMultiplex.h"

class Epoll : public IOMultiplex {
 public:
  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) override;

  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) override;

  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) override;

  virtual void unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                                     bool read_event) override;

  virtual void unregister_write_event(int fd,
                                      IEventDispatcher* event_dispatcher,
                                      bool write_event) override;

  virtual void unregister_read_write_event(
      int fd, IEventDispatcher* event_dispatcher) override;

 public:
  Epoll();
  virtual ~Epoll();

  Epoll(const Epoll&) = delete;
  Epoll& operator=(const Epoll&) = delete;

  Epoll(Epoll&&) = default;
  Epoll& operator=(Epoll&&) = default;

 private:
  int epfd_;

  // <fd, event_flags>
  std::map<int, int32_t> fd_event_flags_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_EPOLL_H_
