#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SESSION_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SESSION_H_

#include <atomic>
#include <memory>

#include "common/msg.h"
#include "net/TCPConnection.h"

class Calc24Server;

class Calc24Session : private std::enable_shared_from_this<Calc24Session> {
 public:
  Calc24Session() = delete;
  virtual ~Calc24Session();

  Calc24Session(const Calc24Session&) = delete;
  Calc24Session& operator=(const Calc24Session&) = delete;

  Calc24Session(Calc24Session&&) = delete;
  Calc24Session& operator=(Calc24Session&&) = delete;

 public:
  explicit Calc24Session(Calc24Server* server,
                         std::shared_ptr<TCPConnection>&& conn);

  int on_read(ByteBuffer& recvbuf);
  int on_write();
  void on_close();
  int get_id() const { return id_; }

  void send_welcome_msg();

 private:
  static int generate_id();

 private:
  int decode_package(ByteBuffer& recvbuf, const MsgHeader& header);

 private:
  int id_;
  Calc24Server* server_;
  std::shared_ptr<TCPConnection> conn_;
};

#endif
