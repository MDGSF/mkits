#include "Calc24Session.h"

#include <functional>

#include "common/msg.h"

Calc24Session::Calc24Session(std::shared_ptr<TCPConnection>&& conn)
    : conn_(std::move(conn)) {
  conn_->set_read_callback(
      std::bind(Calc24Session::on_read, this, std::placeholders::_1));
  conn_->set_write_callback(std::bind(Calc24Session::on_write, this));
  conn_->set_close_callback(std::bind(Calc24Session::on_close, this));
}

int Calc24Session::on_read(ByteBuffer& recvbuf) {
  while (true) {
    if (recvbuf.remaining() <= sizeof(MsgHeader)) {
      return 0;
    }

    MsgHeader header;
    recvbuf.peak(reinterpret_cast<char*>(&header), sizeof(MsgHeader));

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

int Calc24Session::on_write() {}

int Calc24Session::on_close() {}
