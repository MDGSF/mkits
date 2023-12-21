#include "mckits_mos.h"

#include <unistd.h>

char* mckits_working_directory(char* buf, size_t size) {
  return getcwd(buf, size);
}
