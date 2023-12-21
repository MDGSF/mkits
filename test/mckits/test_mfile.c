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

void test02() {
  const char* pathname = "/tmp/mckits_testdir/sub01/subsub01";
  assert(mckits_is_dir_exists(pathname) == 0);
  mckits_mkdir_all(pathname);
  assert(mckits_is_dir_exists(pathname) == 1);

  mckits_remove_dir("/tmp/mckits_testdir");
  assert(mckits_is_dir_exists(pathname) == 0);
  assert(mckits_is_dir_exists("/tmp/mckits_testdir") == 0);
  assert(mckits_is_dir_exists("/tmp") == 1);
}

void test03() {
  const char* pathname = "/tmp/mckits_testfile/not_exists_path/sub01/foo.txt";

  char buf1[1024] = "hello world";
  size_t count = strlen(buf1);
  ssize_t bytes_written = mckits_write_to_file(pathname, buf1, count);
  assert(bytes_written == count);

  mckits_remove_dir("/tmp/mckits_testfile");
  assert(mckits_is_dir_exists("/tmp/mckits_testfile") == 0);
}

int main() {
  test01();
  test02();
  test03();
  return 0;
}

