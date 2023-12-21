#include "mckits_mos.h"

#include <stdio.h>

void test01() {
  char buf[4096] = {0};
  char* p = mckits_working_directory(buf, 4096);
  printf("p = %s\n", p);
  printf("buf = %s\n", buf);
}

int main() {
  test01();
  return 0;
}
