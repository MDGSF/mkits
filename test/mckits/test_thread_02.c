#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "mckits_mos.h"
#include "mckits_thread.h"

void show_current_thread_affinity() {
  int cpus[128] = {0};
  size_t len = 128;
  ssize_t has_affinity_cpu_num = mckits_get_thread_cpu_affinity(cpus, len);
  printf("[%ld]: ", has_affinity_cpu_num);
  for (int i = 0; i < has_affinity_cpu_num; ++i) {
    printf("%d ", cpus[i]);
  }
  printf("\n");
}

void test01() {
  int cores = mckits_hardware_concurrency();
  printf("cores = %d\n", cores);
  show_current_thread_affinity();

  mckits_set_thread_cpu_affinity(0);
  mckits_set_thread_cpu_affinity(1);
  show_current_thread_affinity();

  int cpu_index_list[2] = {5, 8};
  size_t cpu_index_list_len = 2;
  mckits_set_thread_cpu_affinity_list(cpu_index_list, cpu_index_list_len);
  show_current_thread_affinity();

  int except_cpu_index_list[3] = {0, 1, 2};
  size_t except_cpu_index_list_len = 3;
  mckits_set_thread_cpu_affinity_list_except(except_cpu_index_list,
                                             except_cpu_index_list_len);
  show_current_thread_affinity();
}

int main() {
  test01();
  return 0;
}
