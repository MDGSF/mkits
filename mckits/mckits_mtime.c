#include "mckits_mtime.h"

#include <sched.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

int64_t current_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1000000;
}

int64_t current_milliseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int64_t current_microseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

int64_t current_nanoseconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000000 + tv.tv_usec * 1000;
}

int64_t current_clock_seconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec + tp.tv_nsec / 1000000000;
}

int64_t current_clock_milliseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
}

int64_t current_clock_microseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
}

int64_t current_clock_nanoseconds() {
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000000000 + tp.tv_nsec;
}

void sleep_seconds(int seconds) { sleep(seconds); }

void sleep_milliseconds(int64_t milliseconds) {
  sleep_microseconds(milliseconds * 1000);
}

void sleep_microseconds(int64_t microseconds) {
  static const int64_t MAX_MICROSECONDS = 1000000;
  if (microseconds >= MAX_MICROSECONDS) {
    sleep_nanoseconds(microseconds * 1000);
  } else {
    usleep(microseconds);
  }
}

void sleep_nanoseconds(int64_t nanoseconds) {
  struct timespec tp;
  tp.tv_sec = nanoseconds / 1000000000;
  tp.tv_nsec = nanoseconds % 1000000000;
  nanosleep(&tp, NULL);
}

void sleep_to(int64_t microtimestamp) {
  if (microtimestamp - current_clock_microseconds() > 2000) {
    int64_t sleepus = microtimestamp - current_clock_microseconds() - 2000;
    if (sleepus) {
      sleep_microseconds(sleepus);
    }
  }
  while (microtimestamp - current_clock_microseconds() > 1000) {
    sleep_nanoseconds(1);
  }
  while (microtimestamp > current_clock_microseconds()) {
    sched_yield();
  }
}
