#include "TCPServer.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>

#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_msock.h"

int TCPServer::init(const std::string& ip, uint16_t port) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
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

  if (bind(s, (struct sockaddr*)&sa, sizeof(sa)) == -1 ||
      listen(s, 511) == -1) {
    errlog("bind or listen failed: %s", strerror(errno));
    close(s);
    return -1;
  }

  listen_socket_ = s;

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
    int s = mckits_accept_client(listen_socket_);
    if (s <= 0) {
      errlog("accept client failed");
      continue;
    }

    infolog("new client: %d", s);

    // one thread on loop
    std::thread th(&TCPServer::one_loop, this, s);
    th.detach();
  }
}

void TCPServer::one_loop(int sock) {
  for (; running_;) {
    char buf[1024] = {0};
    ssize_t readed_bytes = read(sock, buf, sizeof(buf));
    infolog("%d, %s\n", readed_bytes, buf);
  }
}
