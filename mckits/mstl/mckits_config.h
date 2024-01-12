#ifndef MKITS_MCKITS_MSTL_MCKITS_CONFIG_H_
#define MKITS_MCKITS_MSTL_MCKITS_CONFIG_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MCKITS_OK 0
#define MCKITS_ERROR -1

#define LF (uint8_t)'\n'
#define CR (uint8_t)'\r'
#define CRLF "\r\n"

#define mckits_abs(value) (((value) >= 0) ? (value) : -(value))
#define mckits_min(a, b) ((a) < (b) ? (a) : (b))
#define mckits_max(a, b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
}
#endif

#endif
