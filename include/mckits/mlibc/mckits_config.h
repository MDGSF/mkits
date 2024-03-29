#ifndef MKITS_INCLUDE_MCKITS_MLIBC_MCKITS_CONFIG_H_
#define MKITS_INCLUDE_MCKITS_MLIBC_MCKITS_CONFIG_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__
#define MCKITS_OS_LINUX
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || \
    defined(__NetBSD__)
#define MCKITS_OS_BSD
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

#endif  // MKITS_INCLUDE_MCKITS_MLIBC_MCKITS_CONFIG_H_
