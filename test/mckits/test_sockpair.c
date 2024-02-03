#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mckits/core/mckits_msock.h"
#include "mckits/core/mckits_mtime.h"

void* thread_func1(void* arg) {
  int* ps = (int*)arg;
  int s = *ps;
  while (1) {
    char buf[1024] = "hello";
    write(s, buf, strlen(buf));
    mckits_sleep_seconds(1);
  }
  pthread_exit(NULL);
}

void* thread_func2(void* arg) {
  int* ps = (int*)arg;
  int s = *ps;
  while (1) {
    char buf[1024] = {0};
    ssize_t bytes_readed = read(s, buf, sizeof(buf));
    printf("%ld: %s\n", bytes_readed, buf);
    mckits_sleep_seconds(1);
  }
  pthread_exit(NULL);
}

int main() {
  int sv[2];
  mckits_create_tcp_socketpair(sv);

  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, thread_func1, &sv[0]);
  pthread_create(&thread2, NULL, thread_func2, &sv[1]);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}
