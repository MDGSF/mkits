#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_

#include <atomic>
#include <mutex>
#include <set>
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

  void start();

  void stop();

 private:
  void accept_loop();
  void one_loop(int sock);
  void add_socket(int sock);
  void del_socket(int sock);

  int listen_socket_ = -1;
  std::atomic_bool running_{false};
  std::mutex mtx_;
  std::set<int> client_socks_;
};

#endif
