#ifndef MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_
#define MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_

#include <vector>

#include "net/IEventDispatcher.h"

class IOMultiplex {
 public:
  virtual void poll(int timeout_us,
                    std::vector<IEventDispatcher*>& triggered_fds) = 0;
  virtual void register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                   bool read_event) = 0;
  virtual void register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool write_event) = 0;
};

#endif  // MKITS_APPS_CALC24POINT_NET_IOMULTIPLEX_H_
