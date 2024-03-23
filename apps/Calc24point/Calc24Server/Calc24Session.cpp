#include "Calc24Session.h"

#include <functional>
#include <iostream>
#include <string>

#include "Calc24Server.h"
#include "common/msg.h"

Calc24Session::~Calc24Session() {
  std::cout << "Calc24Session::~Calc24Session, id_ = " << id_ << std::endl;
}

Calc24Session::Calc24Session(Calc24Server* server,
                             std::shared_ptr<TCPConnection>&& conn)
    : server_(server), conn_(std::move(conn)) {
  id_ = generate_id();
  conn_->set_read_callback(
      std::bind(&Calc24Session::on_read, this, std::placeholders::_1));
  conn_->set_write_callback(std::bind(&Calc24Session::on_write, this));
  conn_->set_close_callback(std::bind(&Calc24Session::on_close, this));
  std::cout << "Calc24Session::Calc24Session, id_ = " << id_ << std::endl;
}

int Calc24Session::on_read(ByteBuffer& recvbuf) {
  while (true) {
    if (recvbuf.remaining() <= sizeof(MsgHeader)) {
      return 0;
    }

    MsgHeader header;
    recvbuf.peek(reinterpret_cast<char*>(&header), sizeof(MsgHeader));

    if (header.package_size <= recvbuf.remaining()) {
      if (0 != decode_package(recvbuf, header)) {
        return -1;
      }
    }
  }

  return 0;
}

int Calc24Session::decode_package(ByteBuffer& recvbuf,
                                  const MsgHeader& header) {
  if (static_cast<MsgType>(header.msg_type) == MsgType::MsgTypeWelcome) {
    WelcomeMsg welcome_msg;
    recvbuf.retrieve(reinterpret_cast<char*>(&welcome_msg),
                     sizeof(welcome_msg));

    // TODO, process welcome msg
  }

  return 0;
}

int Calc24Session::on_write() { return 0; }

void Calc24Session::on_close() {
  std::cout << "Calc24Session::on_close" << std::endl;
  server_->on_disconnected(shared_from_this());
}

void Calc24Session::send_welcome_msg() {
  const std::string& welcome_msg = "Welcome to Calc24 Game.";
  conn_->send(welcome_msg);
}

int Calc24Session::generate_id() {
  std::atomic<int> baseid{0};
  return ++baseid;
}
