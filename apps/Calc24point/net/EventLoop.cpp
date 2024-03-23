#include "net/EventLoop.h"

#include <sys/epoll.h>

#include <iostream>
#include <memory>
#include <vector>

#include "net/Epoll.h"
#include "net/IEventDispatcher.h"
#include "net/Poll.h"
#include "net/Select.h"

EventLoop::EventLoop() {}

EventLoop::~EventLoop() {}

int EventLoop::init(IOMultiplexType iotype) {
  if (iotype == IOMultiplexType::IOMultiplexTypeSelect) {
    io_multiplex_ = std::make_unique<Select>();
  } else if (iotype == IOMultiplexType::IOMultiplexTypePoll) {
    io_multiplex_ = std::make_unique<Poll>();
  } else if (iotype == IOMultiplexType::IOMultiplexTypeEpoll) {
    io_multiplex_ = std::make_unique<Epoll>();
  } else {
    printf("Unsupported iotype = %d\n", static_cast<int>(iotype));
    exit(0);
  }
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

void EventLoop::register_read_event(int fd, IEventDispatcher* event_dispatcher,
                                    bool read_event) {
  io_multiplex_->register_read_event(fd, event_dispatcher, read_event);
}

void EventLoop::register_write_event(int fd, IEventDispatcher* event_dispatcher,
                                     bool write_event) {
  io_multiplex_->register_write_event(fd, event_dispatcher, write_event);
}

void EventLoop::unregister_read_event(int fd,
                                      IEventDispatcher* event_dispatcher,
                                      bool read_event) {
  io_multiplex_->unregister_read_event(fd, event_dispatcher, read_event);
}

void EventLoop::unregister_write_event(int fd,
                                       IEventDispatcher* event_dispatcher,
                                       bool write_event) {
  io_multiplex_->unregister_write_event(fd, event_dispatcher, write_event);
}

void EventLoop::unregister_all_event(int fd,
                                     IEventDispatcher* event_dispatcher) {
  io_multiplex_->unregister_read_write_event(fd, event_dispatcher);
}
