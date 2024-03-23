#include "net/Poll.h"

Poll::Poll() {}

Poll::~Poll() {}

void Poll::poll(int timeout_us, std::vector<IEventDispatcher*>& triggered_fds) {
  // poll wait
}

void Poll::register_read_event(int fd, IEventDispatcher* event_dispatcher,
                               bool read_event) {
  // poll
  event_dispatchers_[fd] = event_dispatcher;
}

void Poll::register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                bool write_event) {
  // poll
  event_dispatchers_[fd] = event_dispatcher;
}

void Poll::unregister_read_event(int fd, IEventDispatcher* event_dispatcher,
                                 bool read_event) {}

void Poll::unregister_write_event(int fd, IEventDispatcher* event_dispatcher,
                                  bool write_event) {}

void Poll::unregister_read_write_event(int fd,
                                       IEventDispatcher* event_dispatcher) {}
