#ifndef MKITS_MCKITS_MCKITS_MTIME_H_
#define MKITS_MCKITS_MCKITS_MTIME_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Get current timestamp use gettimeofday().
*/
int64_t current_seconds();
int64_t current_milliseconds();
int64_t current_microseconds();
int64_t current_nanoseconds();

/*
@brief: Get current timestamp use clock_gettime(CLOCK_MONOTONIC);
*/
int64_t current_clock_seconds();
int64_t current_clock_milliseconds();
int64_t current_clock_microseconds();
int64_t current_clock_nanoseconds();

/*
@brief: Sleep a time duration.
*/
void sleep_seconds(int seconds);
void sleep_milliseconds(int64_t milliseconds);
void sleep_microseconds(int64_t microseconds);
void sleep_nanoseconds(int64_t nanoseconds);

/*
@brief: Sleep until a future timestamp.
*/
void sleep_to(int64_t microtimestamp);

#ifdef __cplusplus
}
#endif

#endif
