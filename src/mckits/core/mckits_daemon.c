#include "mckits/core/mckits_daemon.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>

#include "mckits/core/mckits_mlog.h"

static int mckits_check_pid(const char* pidfile) {
  FILE* f = fopen(pidfile, "r");
  if (f == NULL) {
    return 0;
  }

  int pid = 0;
  int n = fscanf(f, "%d", &pid);
  fclose(f);

  if (n == -1 || pid == 0 || pid == getpid()) {
    return 0;
  }

  if (kill(pid, 0) && errno == ESRCH) {
    return 0;
  }

  return pid;
}

static int write_pid(const char* pidfile) {
  int fd = open(pidfile, O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    errlog("can't create pidfile [%s].", pidfile);
    return 0;
  }

  FILE* f = fdopen(fd, "w+");
  if (f == NULL) {
    errlog("can't create pidfile [%s].", pidfile);
    return 0;
  }

  if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
    int pid = 0;
    int n = fscanf(f, "%d", &pid);
    fclose(f);
    if (n != 1) {
      errlog("can't lock and read pidfile.");
    } else {
      errlog("can't lock pidfile, lock is held by pid %d.", pid);
    }
    return 0;
  }

  int pid = getpid();
  if (!fprintf(f, "%d\n", pid)) {
    errlog("can't write pid.");
    close(fd);
    return 0;
  }
  fflush(f);

  return pid;
}

static int redirect_fds() {
  int nullfd = open("/dev/null", O_RDWR);
  if (nullfd == -1) {
    err_ret("unable to open /dev/null: ");
    return -1;
  }
  if (dup2(nullfd, 0) < 0) {
    err_ret("unable to dup2 stdin(0): ");
    return -1;
  }
  if (dup2(nullfd, 1) < 0) {
    err_ret("unable to dup2 stdout(1): ");
    return -1;
  }
  if (dup2(nullfd, 2) < 0) {
    err_ret("unable to dup2 stderr(2): ");
    return -1;
  }
  return 0;
}

int mckits_daemon_init(const char* pidfile) {
  int pid = mckits_check_pid(pidfile);
  if (pid > 0) {
    errlog("already running, pid = %d.", pid);
    return -1;
  }

  if (daemon(1, 1)) {
    errlog("can't daemonize");
    return -1;
  }

  pid = write_pid(pidfile);
  if (pid == 0) {
    return -1;
  }

  if (redirect_fds() != 0) {
    return -1;
  }

  return 0;
}

int mckits_daemon_exit(const char* pidfile) { return unlink(pidfile); }
