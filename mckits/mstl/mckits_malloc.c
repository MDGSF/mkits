#include "mckits_malloc.h"

#include <stdio.h>
#include <stdlib.h>

static void mckits_malloc_oom(size_t size) {
  fprintf(stderr, "malloc: Out of memory trying to allocate %zu bytes\n", size);
  fflush(stderr);
  abort();
}

void* mckits_malloc(size_t size) {
  void* ptr = malloc(size);
  if (ptr == NULL) {
    mckits_malloc_oom(size);
  }
  return ptr;
}

void* mckits_calloc(size_t nmemb, size_t size) {
  void* ptr = calloc(nmemb, size);
  if (ptr == NULL) {
    mckits_malloc_oom(size);
  }
  return ptr;
}

void* mckits_realloc(void* ptr, size_t size) {
  void* ptr = realloc(ptr, size);
  if (ptr == NULL) {
    mckits_malloc_oom(size);
  }
  return ptr;
}

void mckits_free(void* ptr) { free(ptr); }
