#include "mckits_mlibc_utils.h"

int mckits_fequal(float f1, float f2) {
  float diff = f1 - f2;
  return diff < 0.0001f && diff > -0.0001f ? 1 : 0;
}

int mckits_dequal(double f1, double f2) {
  double diff = f1 - f2;
  return diff < 0.0000001f && diff > -0.0000001f ? 1 : 0;
}

int found_int_array(int num, const int* array, size_t size) {
  int found = 0;
  for (size_t i = 0; i < size; ++i) {
    if (num == array[i]) {
      found = 1;
      break;
    }
  }
  return found;
}
