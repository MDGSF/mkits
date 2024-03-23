#include "net/TCPConnection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

TCPConnection::TCPConnection(int clientfd,
                             const std::shared_ptr<EventLoop>& event_loop)
    : fd_(clientfd), event_loop_(event_loop) {}

TCPConnection::~TCPConnection() {
  std::cout << "TCPConnection::~TCPConnection, fd_ = " << fd_ << std::endl;
  ::close(fd_);
}

int TCPConnection::start_read() {
  event_loop_->register_read_event(fd_, this, true);
  return 0;
}

int TCPConnection::send(const char* buf, int buf_len) {
  send_buf_.append(buf, buf_len);

  while (send_buf_.remaining() > 0) {
    int n = ::send(fd_, send_buf_, send_buf_.remaining(), 0);
    if (n == 0) {
      // peer close the connection, so we close connection too.
      on_close();
      return -1;
    } else if (n < 0) {
      if (errno == EINTR) {
        continue;
      } else if (errno == EWOULDBLOCK || errno == EAGAIN) {
        // tcp send buff is full, send failed.
        // register write event to epoll
        register_write_event();
        return 0;
      }

      // error occurs, so we close connection.
      on_close();
      return -1;
    }

    // send `n` bytes success
    send_buf_.erase(n);
  }

  return 0;
}

int TCPConnection::send(const std::string& buf) {
  return send(buf.c_str(), buf.length());
}

void TCPConnection::on_read() {
  if (!enable_read_) {
    return;
  }

  // read data
  char buf[1024] = {0};
  int n = ::recv(fd_, buf, sizeof(buf), 0);
  if (n == 0) {
    // peer close the connection, so we close connection too.
    on_close();
  } else if (n < 0) {
    if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN) {
      return;
    }

    // error occurs, so we close connection.
    on_close();
    return;
  }

  // recv data success
  recv_buf_.append(buf, n);

  if (read_callback_(recv_buf_) != 0) {
    // business login unpack package failed
    // so close connection
    on_close();
  }
}

void TCPConnection::on_write() {
  if (!enable_write_) {
    return;
  }
}

void TCPConnection::on_close() {
  std::cout << "TCPConnection::on_close 1" << std::endl;
  unregister_all_event();
  std::cout << "TCPConnection::on_close 2" << std::endl;
  close_callback_(shared_from_this());
  std::cout << "TCPConnection::on_close 3" << std::endl;
}

void TCPConnection::enable_read(bool read) { enable_read_ = read; }

void TCPConnection::enable_write(bool write) { enable_write_ = write; }

void TCPConnection::register_write_event() {
  if (register_write_event_) {
    return;
  }

  event_loop_->register_write_event(fd_, this, true);
}

void TCPConnection::unregister_write_event() {
  if (!register_write_event_) {
    return;
  }

  event_loop_->register_write_event(fd_, this, false);
  register_write_event_ = false;
}

void TCPConnection::unregister_all_event() {
  event_loop_->unregister_all_event(fd_, this);
}
