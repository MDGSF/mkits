#include "Calc24Server.h"

#include <iostream>

#include "Calc24Session.h"

int Calc24Server::init(int32_t thread_num, const std::string& ip,
                       uint16_t port) {
  tcp_server_.set_connected_callback(
      std::bind(&Calc24Server::on_connected, this, std::placeholders::_1));

  // tcp_server_.set_disconnected_callback(
  //     std::bind(&Calc24Server::on_disconnected, this,
  //     std::placeholders::_1));

  if (0 != tcp_server_.init(thread_num, ip, port)) {
    return -1;
  }

  return 0;
}

void Calc24Server::start() { tcp_server_.start(); }

void Calc24Server::uninit() { tcp_server_.uninit(); }

void Calc24Server::on_connected(std::shared_ptr<TCPConnection>& conn) {
  // 删除无效的 Calc24Session
  pending_deleted_sessions_.clear();

  auto calc24session = std::make_shared<Calc24Session>(this, std::move(conn));
  calc24session->send_welcome_msg();
  int id = calc24session->get_id();
  sessions_[id] = std::move(calc24session);
}

void Calc24Server::on_disconnected(const std::shared_ptr<Calc24Session>& sess) {
  auto iter = sessions_.find(sess->get_id());
  if (iter != sessions_.end()) {
    auto pending_to_delete_session = iter->second;
    pending_deleted_sessions_.push_back(std::move(pending_to_delete_session));
    sessions_.erase(sess->get_id());
    std::cout << "Calc24Server::on_disconnected, session id = "
              << sess->get_id() << std::endl;
  }
}
