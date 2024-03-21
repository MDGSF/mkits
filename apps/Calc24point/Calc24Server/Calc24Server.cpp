#include "Calc24Server.h"

#include "Calc24Session.h"

int Calc24Server::init(int32_t thread_num, const std::string& ip,
                       uint16_t port) {
  tcp_server_.set_connected_callback(
      std::bind(Calc24Server::on_connected, this, std::placeholders::_1));

  if (0 != tcp_server_.init(thread_num, ip, port)) {
    return -1;
  }

  tcp_server_.start();

  return 0;
}

void Calc24Server::uninit() { tcp_server_.uninit(); }

void Calc24Server::on_connected(std::shared_ptr<TCPConnection>& conn) {
  auto calc24session = std::make_shared<Calc24Session>(std::move(conn));
  sessions_.push_back(std::move(calc24session));
}

void Calc24Server::on_disconnected(std::shared_ptr<TCPConnection>& conn) {}
