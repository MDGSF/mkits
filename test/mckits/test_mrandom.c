#include <stdio.h>

#include "mckits_mrandom.h"

void test01() {
  char buf[8] = {0};
  mckits_random_str(buf, sizeof(buf));
  printf("buf = %s\n", buf);
}

void test02() {
  for (int i = 0; i < 10; ++i) {
    int n = mckits_random_num(0, 10);
    printf("%d ", n);
  }
  printf("\n");
}

int main() {
  mckits_random_seed();
  test01();
  test02();
  return 0;
}
