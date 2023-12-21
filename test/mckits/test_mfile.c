#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mckits_mfile.h"

void test01() {
  const char* pathname = "/tmp/mckits_test_file.txt";

  mckits_remove_file(pathname);

  assert(mckits_is_file_exists(pathname) == 0);

  char buf1[1024] = "hello world";
  size_t count = strlen(buf1);
  ssize_t bytes_written = mckits_write_to_file(pathname, buf1, count);
  assert(bytes_written == count);

  assert(mckits_is_file_exists(pathname) == 1);

  ssize_t current_filesize = mckits_file_size(pathname);
  assert(count == current_filesize);

  char buf2[1024] = {0};
  ssize_t bytes_readed = mckits_read_whole_file(pathname, buf2, 1024);
  assert(bytes_written == bytes_readed);
  assert(strcmp(buf1, buf2) == 0);

  mckits_remove_file(pathname);

  assert(mckits_is_file_exists(pathname) == 0);
}

int main() {
  test01();
  return 0;
}

