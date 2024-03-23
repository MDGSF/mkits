#include <signal.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>

#include "Calc24Server.h"
#include "mckits/core/mckits_mlog.h"

void sig_handler(int sig) { printf("sig = %d\n", sig); }

int main(int argc, char** argv) {
  signal(SIGPIPE, SIG_IGN);
  // signal(SIGINT, sig_handler);  // ctrl + C
  // signal(SIGHUP, sig_handler);  // close tty
  // signal(SIGQUIT, sig_handler);
  // signal(SIGTERM, sig_handler);
  // signal(SIGUSR1, sig_handler);
  // signal(SIGKILL, sig_handler);
  // signal(SIGSEGV, sigsegv_handler);
  // signal(SIGBUS, sigsegv_handler);

  mckits_global_loglevel = MKITS_LOG_LEVEL_INFO;

  if (argc != 3) {
    printf("Usage: Calc24Server <ip> <port>\n");
    return 0;
  }

  const char* ip = argv[1];
  const char* port = argv[2];

  Calc24Server server;
  int ret = server.init(1, ip, atoi(port));
  if (ret != 0) {
    errlog("tcp server init failed, ret = %d", ret);
    return 0;
  }

  server.start();

  return 0;
}
