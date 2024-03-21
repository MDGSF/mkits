#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SERVER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SERVER_H_

#include <memory>
#include <vector>

#include "Calc24Session.h"
#include "net/TCPServer.h"

class Calc24Server final {
 public:
  Calc24Server() = default;
  virtual ~Calc24Server() = default;

  int init(int32_t thread_num, const std::string& ip, uint16_t port);
  void uninit();

 private:
  void on_connected(std::shared_ptr<TCPConnection>& conn);
  void on_disconnected(std::shared_ptr<TCPConnection>& conn);

 private:
  TCPServer tcp_server_;
  std::vector<std::shared_ptr<Calc24Session>> sessions_;
};

#endif
