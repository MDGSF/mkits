#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SERVER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_CALC24SERVER_H_

#include <map>
#include <memory>
#include <vector>

#include "Calc24Session.h"
#include "net/TCPServer.h"

class Calc24Server final {
 public:
  Calc24Server() = default;
  virtual ~Calc24Server() = default;

  Calc24Server(const Calc24Server&) = delete;
  Calc24Server& operator=(const Calc24Server&) = delete;

  Calc24Server(Calc24Server&&) = delete;
  Calc24Server& operator=(Calc24Server&&) = delete;

 public:
  int init(int32_t thread_num, const std::string& ip, uint16_t port);
  void start();
  void uninit();
  void on_disconnected(const std::shared_ptr<Calc24Session>& conn);

 private:
  void on_connected(std::shared_ptr<TCPConnection>& conn);

 private:
  TCPServer tcp_server_;
  std::map<int, std::shared_ptr<Calc24Session>> sessions_;
  std::vector<std::shared_ptr<Calc24Session>> pending_deleted_sessions_;
};

#endif
