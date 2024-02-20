#include <stdio.h>

#include "mckits/core/mckits_daemon.h"
#include "mckits/core/mckits_mlog.h"
#include "mckits/core/mckits_mtime.h"

int main() {
  int ret = mckits_daemon_init("test_daemon.pid");
  if (ret != 0) {
    errlog("mckits_daemon_init failed, ret = %d", ret);
    return -1;
  }

  for (;;) {
    mckits_sleep_seconds(1);
  }

  return 0;
}
