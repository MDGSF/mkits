#ifndef MKITS_APPS_CALC24POINT_NET_POLL_H_
#define MKITS_APPS_CALC24POINT_NET_POLL_H_

#include <poll.h>
#include <unistd.h>

#include <map>
#include <vector>

#include "net/IOMultiplex.h"

class Poll : public IOMultiplex {
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
  Poll();
  virtual ~Poll();

  Poll(const Poll&) = delete;
  Poll& operator=(const Poll&) = delete;

  Poll(Poll&&) = default;
  Poll& operator=(Poll&&) = default;

 private:
  // <fd, value>
  std::map<int, IEventDispatcher*> event_dispatchers_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_POLL_H_
