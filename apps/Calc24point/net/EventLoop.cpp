#include "net/EventLoop.h"

#include <sys/epoll.h>

#include <vector>

#include "net/Epoll.h"
#include "net/IEventDispatcher.h"
#include "net/Poll.h"
#include "net/Select.h"

EventLoop::EventLoop() {}

EventLoop::~EventLoop() {}

int EventLoop::init() {
  // io_multiplex_ = new Select();
  // io_multiplex_ = new Poll();
  io_multiplex_ = new Epoll();
  return 0;
}

void EventLoop::run() {
  while (running_) {
    std::vector<IEventDispatcher*> event_dispatchers;
    io_multiplex_->poll(500000, event_dispatchers);
    for (size_t i = 0; i < event_dispatchers.size(); ++i) {
      event_dispatchers[i]->on_read();
      event_dispatchers[i]->on_write();
    }
  }
}

void EventLoop::register_read_event(int fd, bool read_event) {}

void EventLoop::register_write_event(int fd, bool write_event) {}
