#ifndef MKITS_APPS_CALC24POINT_CALC24CLIENT_TCPCLIENT_H_
#define MKITS_APPS_CALC24POINT_CALC24CLIENT_TCPCLIENT_H_

#include <string>

class TCPClient {
 public:
  TCPClient() = default;
  ~TCPClient() = default;

  TCPClient(const TCPClient&) = delete;
  TCPClient& operator=(const TCPClient&) = delete;

  TCPClient(TCPClient&&) = delete;
  TCPClient& operator=(TCPClient&&) = delete;

  int init(const std::string& ip, uint16_t port);

  void run();

 private:
  int sock_ = -1;
};

#endif
