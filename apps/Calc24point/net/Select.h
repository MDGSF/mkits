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
  Select();
  virtual ~Select();

  Select(const Select&) = delete;
  Select& operator=(const Select&) = delete;

  Select(Select&&) = default;
  Select& operator=(Select&&) = default;

 private:
  int maxfd_ = 0;
  fd_set readfds_;
  fd_set writefds_;
  fd_set exceptsfds_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_SELECT_H_
