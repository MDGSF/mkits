#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SESSION_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SESSION_H_

#include "net/TCPConnection.h"

class Calc24Session {
 public:
  Calc24Session(std::shared_ptr<TCPConnection>&& conn);
  virtual ~Calc24Session() = default;

  int on_read(ByteBuffer& recvbuf);
  int on_write();
  int on_close();

 private:
  int decode_package(ByteBuffer& recvbuf, , const MsgHeader& header);

 private:
  std::shared_ptr<TCPConnection> conn_;
};

#endif
