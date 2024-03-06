#include "Player.h"

#include <unistd.h>

Player::Player(int client_fd) : client_fd_(client_fd) {}

Player::~Player() { ::close(client_fd_); }
