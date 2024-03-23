#include "net/TCPServer.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>
#include <thread>

#include "mckits/core/mckits_msock.h"

int TCPServer::init(int32_t thread_num, const std::string& ip, uint16_t port) {
  // TODO: check ip and port here
  ip_ = ip;
  port_ = port;

  thread_pool_.start(thread_num);

  base_event_loop_.init();

  acceptor_ = new Acceptor(&base_event_loop_);

  if (0 != acceptor_->start_listen(ip, port)) {
    return -1;
  }
  acceptor_->set_accept_callback(
      std::bind(&TCPServer::on_accept, this, std::placeholders::_1));

  return 0;
}

void TCPServer::uninit() { thread_pool_.stop(); }

void TCPServer::start() { base_event_loop_.run(); }

void TCPServer::on_accept(int clientfd) {
  std::shared_ptr<EventLoop> event_loop = thread_pool_.get_next_event_loop();
  auto conn = std::make_shared<TCPConnection>(clientfd, event_loop);
  // conn->set_close_callback(
  //     std::bind(&TCPServer::on_disconnected, this, std::placeholders::_1));
  conn->start_read();
  connected_callback_(conn);

  // connections_[clientfd] = std::move(conn);
}

void TCPServer::on_disconnected(const std::shared_ptr<TCPConnection>& conn) {
  disconnected_callback_(conn);
}
