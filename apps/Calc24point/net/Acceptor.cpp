#include "net/Acceptor.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>

#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_msock.h"

Acceptor::Acceptor(EventLoop* event_loop) : event_loop_(event_loop) {}

Acceptor::~Acceptor() {
  if (listen_fd_ != -1) {
    ::close(listen_fd_);
    listen_fd_ = -1;
  }
}

int Acceptor::start_listen(const std::string& ip, uint16_t port) {
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

  listen_fd_ = s;

  event_loop_->register_read_event(listen_fd_, this, true);

  return 0;
}

void Acceptor::on_read() {
  while (true) {
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    int clientfd =
        ::accept(listen_fd_, (struct sockaddr*)&client_addr, &addrlen);
    if (clientfd > 0) {
      // new connection
      accept_callback_(clientfd);
    } else if (clientfd == -1) {
      if (errno == EWOULDBLOCK) {
        // no connection
        return;
      } else {
        // error
        return;
      }
    }
  }
}
