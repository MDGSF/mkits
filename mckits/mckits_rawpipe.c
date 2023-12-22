#include "mckits_rawpipe.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mckits_mlog.h"
#include "mckits_msock.h"

#define close_fd(fd) \
  do {               \
    if (fd != -1) {  \
      close(fd);     \
      fd = -1;       \
    }                \
  } while (0);

static void rawpipe_clear(struct MckitsRawPipe* rawpipe) {
  close_fd(rawpipe->pipe_fd_[0]);
  close_fd(rawpipe->pipe_fd_[1]);
}

struct MckitsRawPipe* mckits_rawpipe_new() {
  struct MckitsRawPipe* rawpipe =
      (struct MckitsRawPipe*)malloc(sizeof(struct MckitsRawPipe));
  rawpipe->pipe_fd_[0] = -1;
  rawpipe->pipe_fd_[1] = -1;
  mckits_rawpipe_reopen(rawpipe);
  return rawpipe;
}

void mckits_rawpipe_drop(struct MckitsRawPipe* rawpipe) {
  rawpipe_clear(rawpipe);
  free(rawpipe);
}

void mckits_rawpipe_reopen(struct MckitsRawPipe* rawpipe) {
  rawpipe_clear(rawpipe);

  if (pipe(rawpipe->pipe_fd_) == -1) {
    errlog("create pipe failed: %s\n", strerror(errno));
    return;
  }

  mckits_set_non_blocking(rawpipe->pipe_fd_[0], 1);
  mckits_set_non_blocking(rawpipe->pipe_fd_[1], 0);
  mckits_set_close_exec(rawpipe->pipe_fd_[0], 1);
  mckits_set_close_exec(rawpipe->pipe_fd_[1], 1);
}

int mckits_rawpipe_read_fd(struct MckitsRawPipe* rawpipe) {
  return rawpipe->pipe_fd_[0];
}

int mckits_rawpipe_write_fd(struct MckitsRawPipe* rawpipe) {
  return rawpipe->pipe_fd_[1];
}

int mckits_rawpipe_write(struct MckitsRawPipe* rawpipe, const void* buf,
                         size_t count) {
  int ret = 0;
  do {
    ret = write(rawpipe->pipe_fd_[1], buf, count);
  } while (ret == -1 && errno == EINTR);
  return ret;
}

int mckits_rawpipe_read(struct MckitsRawPipe* rawpipe, void* buf,
                        size_t count) {
  int ret = 0;
  do {
    ret = read(rawpipe->pipe_fd_[0], buf, count);
  } while (ret == -1 && errno == EINTR);
  return ret;
}

