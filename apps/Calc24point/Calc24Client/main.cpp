#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "TCPClient.h"
#include "mckits/core/mckits_mlog.h"

int main(int argc, char** argv) {
  mckits_global_loglevel = MKITS_LOG_LEVEL_INFO;

  if (argc != 3) {
    printf("Usage: Calc24Client <ip> <port>\n");
    return 0;
  }

  const char* ip = argv[1];
  const char* port = argv[2];

  TCPClient client;
  int ret = client.init(ip, atoi(port));
  if (ret != 0) {
    errlog("tcp client connect to server failed, ret = %d", ret);
    return 0;
  }

  client.run();

  return 0;
}
