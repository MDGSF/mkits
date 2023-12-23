#ifndef MKITS_MCKITS_MCKITS_UTILS_H_
#define MKITS_MCKITS_MCKITS_UTILS_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define mckits_min(a, b) ((a) < (b) ? (a) : (b))
#define mckits_max(a, b) ((a) > (b) ? (a) : (b))

#define mckits_assert(expression, ...)                         \
  do {                                                         \
    if (!(expression)) {                                       \
      char str[4096];                                          \
      snprintf(str, sizeof str, __VA_ARGS__);                  \
      fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, str); \
      abort();                                                 \
    }                                                          \
  } while (0)

/*
@brief: Determine the equality of two floating-point numbers with
  a precision of 0.0001.
@return: 1 means equal, 0 means not equal
*/
int mckits_fequal(float f1, float f2);

/*
@brief: Determine the equality of two floating-point numbers with
  a precision of 0.0000001.
@return: 1 means equal, 0 means not equal
*/
int mckits_dequal(double f1, double f2);

#ifdef __cplusplus
}
#endif

#endif
