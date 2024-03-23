#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_TCPSERVER_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Player.h"

class TCPServer {
 public:
  TCPServer() = default;
  ~TCPServer() = default;

  TCPServer(const TCPServer&) = delete;
  TCPServer& operator=(const TCPServer&) = delete;

  TCPServer(TCPServer&&) = delete;
  TCPServer& operator=(TCPServer&&) = delete;

 public:
  int init(const std::string& ip, uint16_t port);

  void start();

  void stop();

 private:
  void accept_loop();
  void one_loop(int sock);

  void new_player_joined(int client_fd);

  int send_welcome_msg(int fd);
  int send_cards(int fd);
  std::string init_cards();

  int handle_client_msg(int client_fd);
  int send_msg_to_other_clients(int msg_owner_client_fd,
                                const std::string& msg);
  int send_msg_to_client(int client_fd, const std::string& msg);

  int listen_socket_ = -1;
  std::atomic_bool running_{false};

  // <client_fd, thread_handle>, TODO: shared_ptr -> unique_ptr
  std::unordered_map<int, std::shared_ptr<std::thread>> client_fd_to_threads_;
  std::mutex mutex_for_client_fd_to_threads_;

  // <client_fd, recv_buf>
  std::unordered_map<int, std::string> client_fd_to_recvbuf_;

  std::unordered_map<int, std::shared_ptr<std::mutex>> client_fd_to_mutex_;

  std::vector<Desk> desks_;

  // <client_fd, client_fd player is ready>
  std::unordered_map<int, bool> client_fd_to_desk_ready_;
};

#endif
