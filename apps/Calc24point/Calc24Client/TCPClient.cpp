#include "TCPClient.h"

#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_msock.h"

int TCPClient::init(const std::string& ip, uint16_t port) {
  int s = mckits_tcpconnect(ip.c_str(), port, 1);
  if (s <= 0) {
    errlog("tcp connect to [%s:%d] failed, ret = %d", ip.c_str(), port, s);
    return -1;
  }

  sock_ = s;

  return 0;
}
