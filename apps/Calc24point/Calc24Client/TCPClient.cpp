#include "TCPClient.h"

#include <unistd.h>

#include <cstring>

#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_msock.h"
#include "mckits/core/mckits_mtime.h"

int TCPClient::init(const std::string& ip, uint16_t port) {
  int s = mckits_tcpconnect(ip.c_str(), port, 0);
  if (s <= 0) {
    errlog("tcp connect to [%s:%d] failed, ret = %d", ip.c_str(), port, s);
    return -1;
  }

  sock_ = s;

  return 0;
}

void TCPClient::run() {
  for (;;) {
    char buf[1024] = "hello";
    ssize_t write_bytes = write(sock_, buf, strlen(buf));
    if (write_bytes != strlen(buf)) {
      errlog("write failed");
      break;
    }

    memset(buf, 0, sizeof(buf));
    ssize_t read_bytes = read(sock_, buf, sizeof(buf));
    if (read_bytes <= 0) {
      errlog("read failed");
      break;
    }
    infolog("%d, %s", read_bytes, buf);

    mckits_sleep_seconds(1);
  }
}
