#ifndef MKITS_APPS_CALC24POINT_NET_POLL_H_
#define MKITS_APPS_CALC24POINT_NET_POLL_H_

#include <poll.h>
#include <unistd.h>

#include <map>
#include <vector>

#include "net/IOMultiplex.h"

class Poll : public IOMultiplex {
 public:
  Poll();
  virtual ~Poll();

  Poll(const Poll&) = default;
  Poll& operator=(const Poll&) = default;

  Poll(Poll&&) = default;
  Poll& operator=(Poll&&) = default;

  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) override;
  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) override;
  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) override;

 private:
  struct pollfd* pollfd_;

  // <fd, value>
  std::map<int, IEventDispatcher*> event_dispatchers_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_POLL_H_
