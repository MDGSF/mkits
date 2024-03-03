#include "TCPServer.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <thread>

#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_mrandom.h"
#include "mckits/core/mckits_msock.h"
#include "mcppkits/mstl/mcppkits_defer.h"

int TCPServer::init(const std::string& ip, uint16_t port) {
  int s = ::socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1) {
    errlog("create socket failed: %s", strerror(errno));
    return -1;
  }

  mckits_set_reuse_addr(s, 1);
  mckits_set_reuse_port(s, 1);

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = inet_addr(ip.c_str());

  if (::bind(s, (struct sockaddr*)&sa, sizeof(sa)) == -1 ||
      ::listen(s, 511) == -1) {
    errlog("bind or listen failed: %s", strerror(errno));
    close(s);
    return -1;
  }

  listen_socket_ = s;

  mckits_random_seed();

  return 0;
}

void TCPServer::start() {
  std::thread th(&TCPServer::accept_loop, this);
  th.join();
}

void TCPServer::stop() {
  running_ = false;
  close(listen_socket_);
}

void TCPServer::accept_loop() {
  running_ = true;

  for (; running_;) {
    int client_fd = mckits_accept_client(listen_socket_);
    if (client_fd <= 0) {
      errlog("accept client failed");
      break;
    }

    new_player_joined(client_fd);
  }
}

void TCPServer::new_player_joined(int client_fd) {
  Desk* pcurrent_desk = nullptr;
  auto iter = desks_.rbegin();
  if (iter == desks_.rend()) {
    Desk new_desk;
    new_desk.id = 0;
    new_desk.clientfd1 = client_fd;
    desks_.push_back(new_desk);
  } else {
    if (iter->clientfd1 == NO_PLAYER_ON_SEAET) {
      iter->clientfd1 = client_fd;
    } else if (iter->clientfd2 == NO_PLAYER_ON_SEAET) {
      iter->clientfd2 = client_fd;
    } else if (iter->clientfd3 == NO_PLAYER_ON_SEAET) {
      iter->clientfd3 = client_fd;
      pcurrent_desk = &(*iter);  // enough player to start calc24 game.
    } else {
      Desk new_desk;
      new_desk.id = desks_.size();
      new_desk.clientfd1 = client_fd;
      desks_.push_back(new_desk);
    }
  }

  auto sp_thread =
      std::make_shared<std::thread>(&TCPServer::one_loop, this, client_fd);
  client_fd_to_threads_[client_fd] = std::move(sp_thread);
  client_fd_to_recvbuf_[client_fd] = "";
  client_fd_to_mutex_[client_fd] = std::make_shared<std::mutex>();

  if (pcurrent_desk != nullptr) {
    // start calc24 game for current desk.
  }
}

void TCPServer::one_loop(int client_fd) {
  infolog("new client: %d", client_fd);

  DEFER([&]() { ::close(client_fd); });

  int ret = send_welcome_msg(client_fd);
  if (ret != 0) {
    return;
  }

  ret = send_cards(client_fd);
  if (ret != 0) {
    return;
  }

  for (; running_;) {
    char buf[1024] = {0};
    ssize_t read_bytes = read(client_fd, buf, sizeof(buf));
    if (read_bytes <= 0) {
      errlog("read failed");
      break;
    }
    infolog("%d, %s", read_bytes, buf);

    std::string& recv_buf = client_fd_to_recvbuf_[client_fd];
    recv_buf.append(buf, read_bytes);

    ret = handle_client_msg(client_fd);
    if (ret != 0) {
      return;
    }
  }
}

int TCPServer::send_welcome_msg(int fd) {
  static const char* welcome_msg = "Welcome to Calc24 Game.\n";
  ssize_t write_bytes = write(fd, welcome_msg, strlen(welcome_msg));
  if (write_bytes != static_cast<ssize_t>(strlen(welcome_msg))) {
    errlog("write failed");
    return -1;
  }
  return 0;
}

int TCPServer::send_cards(int fd) {
  std::string cards = init_cards();
  ssize_t write_bytes = write(fd, cards.c_str(), cards.size());
  if (write_bytes != (ssize_t)cards.size()) {
    errlog("write failed");
    return -1;
  }
  return 0;
}

std::string TCPServer::init_cards() {
  static constexpr char cards[] = {'A', '2', '3', '4', '5', '6', '7', '8',
                                   '9', 'x', 'J', 'Q', 'K', 'w', 'W'};
  static constexpr int cards_size = sizeof(cards) / sizeof(cards[0]);
  std::stringstream ss;
  ss << "Your cards is:";
  for (int i = 0; i < 4; ++i) {
    int card_idx = mckits_random_num(0, cards_size);
    char card = cards[card_idx];
    std::cout << card_idx << " " << card << std::endl;
    ss << " " << card;
  }
  ss << std::endl;
  return ss.str();
}

// ABC\nDEF\nGH
int TCPServer::handle_client_msg(int client_fd) {
  std::string& recv_buf = client_fd_to_recvbuf_[client_fd];
  for (size_t index = 0; index < recv_buf.length();) {
    if (recv_buf[index] == '\n') {
      std::string msg = recv_buf.substr(0, index + 1);
      recv_buf.erase(0, index + 1);
      std::cout << "client[" << client_fd << "] says: " << msg << std::endl;
      send_msg_to_other_clients(client_fd, msg);
      index = 0;
      continue;
    }
    ++index;
  }
  return 0;
}

int TCPServer::send_msg_to_other_clients(int msg_owner_client_fd,
                                         const std::string& msg) {
  std::lock_guard<std::mutex> lock(mutex_for_client_fd_to_threads_);

  for (const auto& client : client_fd_to_threads_) {
    int other_client_fd = client.first;
    if (other_client_fd == msg_owner_client_fd) {
      continue;
    }

    std::string msg_with_owner_info =
        "client[" + std::to_string(msg_owner_client_fd) + "] says: " + msg;
    int ret = send_msg_to_client(other_client_fd, msg_with_owner_info);
    if (ret != 0) {
      return ret;
    }
  }
  return 0;
}

int TCPServer::send_msg_to_client(int client_fd, const std::string& msg) {
  std::lock_guard<std::mutex> lock(*client_fd_to_mutex_[client_fd]);

  // TODO, write long msg, may need write multi-times.
  ssize_t write_bytes = write(client_fd, msg.c_str(), msg.size());
  if (write_bytes != (ssize_t)msg.size()) {
    errlog("write failed");
    return -1;
  }
  return 0;
}
