#ifndef MKITS_APPS_CALC24POINT_NET_TCPSERVER_H_
#define MKITS_APPS_CALC24POINT_NET_TCPSERVER_H_

#include <cstdint>
#include <map>
#include <string>

#include "net/Acceptor.h"
#include "net/EventLoop.h"
#include "net/TCPConnection.h"
#include "net/ThreadPool.h"

using OnConnectedCallback =
    std::function<void(std::shared_ptr<TCPConnection>& conn)>;
using OnDisconnectedCallback =
    std::function<void(std::shared_ptr<TCPConnection>& conn)>;

class TCPServer {
 public:
  TCPServer() = default;
  virtual ~TCPServer() = default;

  TCPServer(const TCPServer&) = default;
  TCPServer& operator=(const TCPServer&) = default;

  TCPServer(TCPServer&&) = default;
  TCPServer& operator=(TCPServer&&) = default;

  int init(int32_t thread_num, const std::string& ip, uint16_t port);
  void uninit();
  void start();

  void set_connected_callback(OnConnectedCallback&& callback) {
    connected_callback_ = std::move(callback);
  }

  void set_disconnected_callback(OnDisconnectedCallback&& callback) {
    disconnected_callback_ = std::move(callback);
  }

 private:
  void on_accept(int clientfd);

 private:
  int listen_fd_{-1};
  uint16_t port_;
  std::string ip_;
  ThreadPool thread_pool_;
  EventLoop base_event_loop_;
  Acceptor* acceptor_;
  std::map<int, std::shared_ptr<TCPConnection>> connections_;
  OnConnectedCallback connected_callback_;
  OnDisconnectedCallback disconnected_callback_;
};

#endif  // MKITS_APPS_CALC24POINT_NET_TCPSERVER_H_
