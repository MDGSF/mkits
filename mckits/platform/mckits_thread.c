#define _GNU_SOURCE

#include "mckits_thread.h"

#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "mckits_mlibc_utils.h"
#include "mckits_mlog.h"
#include "mckits_mos.h"

void mckits_set_thread_name(const char* name) {
  int ret = pthread_setname_np(pthread_self(), name);
  if (ret != 0) {
    errlog("pthread setname failed, ret = %d, %s\n", ret, strerror(errno));
  }
}

void mckits_get_thread_name(char* name, size_t len) {
  int ret = pthread_getname_np(pthread_self(), name, len);
  if (ret != 0) {
    errlog("pthread getname failed, ret = %d, %s\n", ret, strerror(errno));
  }
}

void mckits_set_thread_cpu_affinity(int cpu_index) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  if (cpu_index >= 0) {
    // Set affinity mask to include CPUS[cpu_index]
    CPU_SET(cpu_index, &cpuset);
  } else {
    // Set affinity mask to include CPUS[0 ~ cores]
    int cores = mckits_hardware_concurrency();
    for (int i = 0; i < cores; ++i) {
      CPU_SET(i, &cpuset);
    }
  }

  int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  if (ret != 0) {
    errlog("pthread setaffinity failed: %d, %s", ret, strerror(errno));
  }
}

void mckits_set_thread_cpu_affinity_list(const int* cpu_index_list,
                                         size_t cpu_index_list_len) {
  int cores = mckits_hardware_concurrency();
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  for (size_t i = 0; i < cpu_index_list_len; ++i) {
    int cpu_index = cpu_index_list[i];
    if (cpu_index < 0 || cpu_index >= cores) {
      errlog("invalid cpu_index: %d, cores = %d\n", cpu_index, cores);
      return;
    }
    CPU_SET(cpu_index, &cpuset);
  }

  int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  if (ret != 0) {
    errlog("pthread setaffinity failed: %d, %s", ret, strerror(errno));
  }
}

void mckits_set_thread_cpu_affinity_list_except(const int* cpu_index_list,
                                                size_t cpu_index_list_len) {
  int cores = mckits_hardware_concurrency();
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  for (int cpu_index = 0; cpu_index < cores; ++cpu_index) {
    if (0 == found_int_array(cpu_index, cpu_index_list, cpu_index_list_len)) {
      CPU_SET(cpu_index, &cpuset);
    }
  }

  int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  if (ret != 0) {
    errlog("pthread setaffinity failed: %d, %s", ret, strerror(errno));
  }
}

ssize_t mckits_get_thread_cpu_affinity(int* cpus, size_t len) {
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  int ret = pthread_getaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  if (ret != 0) {
    errlog("pthread getaffinity failed: %d, %s", ret, strerror(errno));
    return -1;
  }

  ssize_t count = 0;
  for (int i = 0; i < CPU_SETSIZE; ++i) {
    if (CPU_ISSET(i, &cpuset)) {
      cpus[count++] = i;
      if (count >= len) {
        return -2;
      }
    }
  }

  return count;
}
