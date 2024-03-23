#ifndef MKITS_APPS_CALC24POINT_NET_TCPCONNECTION_H_
#define MKITS_APPS_CALC24POINT_NET_TCPCONNECTION_H_

#include <functional>
#include <memory>
#include <string>

#include "net/ByteBuffer.h"
#include "net/EventLoop.h"
#include "net/IEventDispatcher.h"

class TCPConnection;

using ReadCallback = std::function<int(ByteBuffer&)>;
using WriteCallback = std::function<int()>;
using CloseCallback =
    std::function<void(const std::shared_ptr<TCPConnection>&)>;

class TCPConnection : public IEventDispatcher,
                      public std::enable_shared_from_this<TCPConnection> {
 public:
  virtual void on_read() override;
  virtual void on_write() override;
  virtual void on_close() override;
  virtual void enable_read(bool read) override;
  virtual void enable_write(bool write) override;

 public:
  TCPConnection() = delete;
  virtual ~TCPConnection();

  TCPConnection(const TCPConnection&) = default;
  TCPConnection& operator=(const TCPConnection&) = default;

  TCPConnection(TCPConnection&&) = default;
  TCPConnection& operator=(TCPConnection&&) = default;

 public:
  TCPConnection(int clientfd, const std::shared_ptr<EventLoop>& event_loop);

  int start_read();

  void set_read_callback(ReadCallback&& read_callback) {
    read_callback_ = std::move(read_callback);
  }

  void set_write_callback(WriteCallback&& write_callback) {
    write_callback_ = std::move(write_callback);
  }

  void set_close_callback(CloseCallback&& close_callback) {
    close_callback_ = std::move(close_callback);
  }

  int send(const char* buf, int buf_len);
  int send(const std::string& buf);

 private:
  void register_write_event();
  void unregister_write_event();

  void unregister_all_event();

 private:
  int fd_{0};
  bool register_write_event_{false};
  bool enable_read_{false};
  bool enable_write_{false};
  ByteBuffer recv_buf_;
  ByteBuffer send_buf_;
  ReadCallback read_callback_;
  WriteCallback write_callback_;
  CloseCallback close_callback_;
  std::shared_ptr<EventLoop> event_loop_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_TCPCONNECTION_H_
