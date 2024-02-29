#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_

#include <string>

class TCPServer {
 public:
  TCPServer() = default;
  ~TCPServer() = default;

  TCPServer(const TCPServer&) = delete;
  TCPServer& operator=(const TCPServer&) = delete;

  TCPServer(TCPServer&&) = delete;
  TCPServer& operator=(TCPServer&&) = delete;

  int init(const std::string& ip, uint16_t port);

 private:
};

#endif
