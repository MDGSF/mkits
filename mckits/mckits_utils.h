#ifndef MKITS_MCKITS_MCKITS_UTILS_H_
#define MKITS_MCKITS_MCKITS_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define mckits_min(a, b) ((a) < (b) ? (a) : (b))
#define mckits_max(a, b) ((a) > (b) ? (a) : (b))

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
