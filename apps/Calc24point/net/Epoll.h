#ifndef MKITS_APPS_CALC24POINT_NET_EPOLL_H_
#define MKITS_APPS_CALC24POINT_NET_EPOLL_H_

#include <sys/epoll.h>
#include <unistd.h>

#include <vector>

#include "net/IOMultiplex.h"

class Epoll : public IOMultiplex {
 public:
  Epoll();
  virtual ~Epoll();

  Epoll(const Epoll&) = default;
  Epoll& operator=(const Epoll&) = default;

  Epoll(Epoll&&) = default;
  Epoll& operator=(Epoll&&) = default;

  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) override;
  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) override;
  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) override;

 private:
  int epfd_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_EPOLL_H_
