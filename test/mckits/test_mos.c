#include <stdio.h>

#include "mckits_mos.h"

void test01() {
  char buf[4096] = {0};
  char* p = mckits_working_directory(buf, 4096);
  printf("working directory p = %s\n", p);
  printf("working directory buf = %s\n", buf);

  char exe_path[4096] = {0};
  mckits_exe_path(exe_path, 4096);
  printf("exe_path = %s\n", exe_path);

  char exe_path_dir[4096] = {0};
  mckits_exe_path_dir(exe_path_dir, 4096);
  printf("exe_path_dir = %s\n", exe_path_dir);

  char exe_path_base[4096] = {0};
  mckits_exe_path_base(exe_path_base, 4096);
  printf("exe_path_base = %s\n", exe_path_base);
}

int main() {
  test01();
  return 0;
}
