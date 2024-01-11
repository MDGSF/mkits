#include "mckits_mtime.h"

#include <sched.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int64_t mckits_current_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1000000;
}

int64_t mckits_current_milliseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int64_t mckits_current_microseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

int64_t mckits_current_nanoseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000000 + tv.tv_usec * 1000;
}

int64_t mckits_current_clock_seconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec + tp.tv_nsec / 1000000000;
}

int64_t mckits_current_clock_milliseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
}

int64_t mckits_current_clock_microseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
}

int64_t mckits_current_clock_nanoseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000000000 + tp.tv_nsec;
}

void mckits_sleep_seconds(int seconds) { sleep(seconds); }

void mckits_sleep_milliseconds(int64_t milliseconds) {
  mckits_sleep_microseconds(milliseconds * 1000);
}

void mckits_sleep_microseconds(int64_t microseconds) {
  static const int64_t MAX_MICROSECONDS = 1000000;
  if (microseconds >= MAX_MICROSECONDS) {
    mckits_sleep_nanoseconds(microseconds * 1000);
  } else {
    usleep(microseconds);
  }
}

void mckits_sleep_nanoseconds(int64_t nanoseconds) {
  struct timespec tp;
  tp.tv_sec = nanoseconds / 1000000000;
  tp.tv_nsec = nanoseconds % 1000000000;
  nanosleep(&tp, NULL);
}

void mckits_sleep_to(int64_t microtimestamp) {
  if (microtimestamp - mckits_current_clock_microseconds() > 2000) {
    int64_t sleepus =
        microtimestamp - mckits_current_clock_microseconds() - 2000;
    if (sleepus) {
      mckits_sleep_microseconds(sleepus);
    }
  }
  while (microtimestamp - mckits_current_clock_microseconds() > 1000) {
    mckits_sleep_nanoseconds(1);
  }
  while (microtimestamp > mckits_current_clock_microseconds()) {
    sched_yield();
  }
}
