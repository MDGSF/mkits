#ifndef MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_
#define MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_

#include <functional>
#include <string>

#include "net/EventLoop.h"
#include "net/IEventDispatcher.h"

using AcceptCallback = std::function<void(int)>;

class Acceptor final : public IEventDispatcher {
 public:
  Acceptor(EventLoop* event_loop);
  virtual ~Acceptor();

  Acceptor(const Acceptor&) = default;
  Acceptor& operator=(const Acceptor&) = default;

  Acceptor(Acceptor&&) = default;
  Acceptor& operator=(Acceptor&&) = default;

  void set_accept_callback(AcceptCallback&& accept_callback) {
    accept_callback_ = std::move(accept_callback);
  }

  void on_accept(int clientfd);

  int start_listen(const std::string& ip, uint16_t port);

 public:
  virtual void on_read() override;

 private:
  virtual void on_write() override {}
  virtual void on_close() override {}
  virtual void enable_read(bool read) override {}
  virtual void enable_write(bool write) override {}

 private:
  int listenfd_{-1};
  EventLoop* event_loop_{nullptr};
  AcceptCallback accept_callback_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_
