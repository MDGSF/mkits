#ifndef MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_
#define MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_

#include "net/IOMultiplex.h"

class EventLoop final {
 public:
  EventLoop();
  virtual ~EventLoop();

  EventLoop(const EventLoop&) = default;
  EventLoop& operator=(const EventLoop&) = default;

  EventLoop(EventLoop&&) = default;
  EventLoop& operator=(EventLoop&&) = default;

  int init();
  void run();
  void register_read_event(int fd, bool read_event);
  void register_write_event(int fd, bool write_event);

 private:
  bool running_;
  int epfd_;
  IOMultiplex* io_multiplex_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_EVENT_LOOP_H_
