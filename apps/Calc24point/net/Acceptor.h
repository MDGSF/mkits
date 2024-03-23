#ifndef MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_
#define MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_

#include <functional>
#include <string>

#include "net/EventLoop.h"
#include "net/IEventDispatcher.h"

using AcceptCallback = std::function<void(int)>;

class Acceptor final : public IEventDispatcher {
 public:
  virtual void on_read() override;
  virtual void on_write() override {}
  virtual void on_close() override {}
  virtual void enable_read(bool read) override {}
  virtual void enable_write(bool write) override {}

 public:
  Acceptor() = delete;
  virtual ~Acceptor();

  Acceptor(const Acceptor&) = delete;
  Acceptor& operator=(const Acceptor&) = delete;

  Acceptor(Acceptor&&) = delete;
  Acceptor& operator=(Acceptor&&) = delete;

 public:
  explicit Acceptor(EventLoop* event_loop);

  void set_accept_callback(AcceptCallback&& accept_callback) {
    accept_callback_ = std::move(accept_callback);
  }

  int start_listen(const std::string& ip, uint16_t port);

 private:
  int listen_fd_{-1};
  EventLoop* event_loop_{nullptr};
  AcceptCallback accept_callback_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_ACCEPTOR_H_
