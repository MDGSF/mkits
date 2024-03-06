#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_PLAYER_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_PLAYER_H_

#include <memory>
#include <string>

#include "Desk.h"

class Player final {
 public:
  Player() = delete;
  explicit Player(int client_fd);
  ~Player();

  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

 private:
  const int client_fd_;
  bool ready_{false};
  std::string recv_buf_{};
  std::weak_ptr<Desk> pdesk_{};
};

#endif
