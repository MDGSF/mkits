#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits/core/mckits_thread.h"

void test01() {
  char name[16] = {0};
  mckits_get_thread_name(name, 16);
  printf("name = %s\n", name);

  const char* new_thread_name = "hello_mckits";
  mckits_set_thread_name(new_thread_name);

  mckits_get_thread_name(name, 16);
  printf("name = %s\n", name);

  assert(strcmp(new_thread_name, name) == 0);
}

int main() {
  test01();
  return 0;
}
