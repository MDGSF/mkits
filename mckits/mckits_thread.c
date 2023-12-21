#define _GNU_SOURCE

#include "mckits_thread.h"

#include <errno.h>
#include <pthread.h>
#include <string.h>

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
    int cores = hardware_concurrency();
    for (int i = 0; i < cores; ++i) {
      CPU_SET(i, &cpuset);
    }
  }

  int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
  if (ret != 0) {
    errlog("pthread setaffinity failed: %d, %s", ret, strerror(errno));
  }
}
