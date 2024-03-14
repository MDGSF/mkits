#ifndef MKITS_APPS_CALC24POINT_NET_SELECT_H_
#define MKITS_APPS_CALC24POINT_NET_SELECT_H_

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <vector>

#include "net/IOMultiplex.h"

class Select : public IOMultiplex {
 public:
  Select();
  virtual ~Select();

  Select(const Select&) = default;
  Select& operator=(const Select&) = default;

  Select(Select&&) = default;
  Select& operator=(Select&&) = default;

  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) override;
  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) override;
  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) override;

 private:
  int maxfd_ = 0;
  fd_set readfds_;
  fd_set writefds_;
  fd_set exceptsfds_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_SELECT_H_
