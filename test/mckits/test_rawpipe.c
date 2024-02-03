#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/core/mckits_rawpipe.h"

void test01() {
  struct MckitsRawPipe* rawpipe = mckits_rawpipe_new();

  char in[1024] = "hello world";
  size_t inlen = strlen(in);
  int bytes_written = mckits_rawpipe_write(rawpipe, in, inlen);
  assert(bytes_written == inlen);

  char out[1024] = {0};
  size_t outlen = 1024;
  int bytes_readed = mckits_rawpipe_read(rawpipe, out, outlen);
  printf("%d: %s\n", bytes_readed, out);

  mckits_rawpipe_drop(rawpipe);
}

int main() {
  test01();
  return 0;
}
