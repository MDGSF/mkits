#include "mckits_mfile.h"

#include <stdio.h>
#include <stdlib.h>

ssize_t mckits_read_whole_file(const char* pathname, void* buf, size_t count) {
  FILE* file = fopen(pathname, "rb");
  if (file == NULL) {
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (file_size > count) {
    fclose(file);
    return -1;
  }

  size_t read_size = fread(buf, 1, file_size, file);
  fclose(file);

  if (read_size != file_size) {
    return -1;
  }

  return read_size;
}
