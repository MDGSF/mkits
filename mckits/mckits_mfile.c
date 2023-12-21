#include "mckits_mfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int mckits_is_file_exists(const char* pathname) {
  return access(pathname, F_OK) == 0 ? 1 : 0;
}

ssize_t mckits_file_size(const char* pathname) {
  struct stat st;
  return stat(pathname, &st) == 0 ? st.st_size : -1;
}

void mckits_remove_file(const char* pathname) { remove(pathname); }

ssize_t mckits_read_whole_file(const char* pathname, void* buf, size_t count) {
  FILE* file = fopen(pathname, "rb");
  if (file == NULL) {
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (file_size < 0) {
    fclose(file);
    return -2;
  }

  if (file_size > count) {
    fclose(file);
    return -3;
  }

  size_t read_size = fread(buf, 1, file_size, file);
  fclose(file);

  if (read_size != file_size) {
    return -4;
  }

  return read_size;
}

ssize_t mckits_write_to_file(const char* pathname, const void* buf,
                             size_t count) {
  FILE* file = fopen(pathname, "w");
  if (file == NULL) {
    return -1;
  }
  size_t bytes_written = fwrite(buf, 1, count, file);
  fclose(file);
  return bytes_written;
}

