#ifndef MKITS_MCKITS_MCKITS_MTIME_H_
#define MKITS_MCKITS_MCKITS_MTIME_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Get current timestamp use gettimeofday().
*/
int64_t mckits_current_seconds();
int64_t mckits_current_milliseconds();
int64_t mckits_current_microseconds();
int64_t mckits_current_nanoseconds();

/*
@brief: Get current timestamp use clock_gettime(CLOCK_MONOTONIC);
*/
int64_t mckits_current_clock_seconds();
int64_t mckits_current_clock_milliseconds();
int64_t mckits_current_clock_microseconds();
int64_t mckits_current_clock_nanoseconds();

/*
@brief: Sleep a time duration.
*/
void mckits_sleep_seconds(int seconds);
void mckits_sleep_milliseconds(int64_t milliseconds);
void mckits_sleep_microseconds(int64_t microseconds);
void mckits_sleep_nanoseconds(int64_t nanoseconds);

/*
@brief: Sleep until a future timestamp.
@notes: The function exhibits an error within the realm of tens of microseconds,
  while simultaneously demanding a greater share of CPU resources.
*/
void mckits_sleep_to(int64_t microtimestamp);

#ifdef __cplusplus
}
#endif

#endif
