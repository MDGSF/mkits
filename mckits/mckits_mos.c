#include "mckits_mos.h"

#include <unistd.h>

#include "mckits_mfile.h"

char* mckits_working_directory(char* buf, size_t size) {
  return getcwd(buf, size);
}

ssize_t mckits_exe_path(char* buf, size_t bufsiz) {
  return readlink("/proc/self/exe", buf, bufsiz - 1);
}

ssize_t mckits_exe_path_dir(char* buf, size_t bufsiz) {
  char exe_path[4096] = {0};
  ssize_t ret = mckits_exe_path(exe_path, sizeof exe_path);
  if (ret < 0) {
    return ret;
  }
  return mckits_path_dir(exe_path, buf, bufsiz);
}

ssize_t mckits_exe_path_base(char* buf, size_t bufsiz) {
  char exe_path[4096] = {0};
  ssize_t ret = mckits_exe_path(exe_path, sizeof exe_path);
  if (ret < 0) {
    return ret;
  }
  return mckits_path_base(exe_path, buf, bufsiz);
}

int hardware_concurrency() {
  long cores = sysconf(_SC_NPROCESSORS_ONLN);
  return (int)cores;
}
