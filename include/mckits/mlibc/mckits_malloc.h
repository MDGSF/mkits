#ifndef MKITS_MCKITS_MLIBC_MCKITS_MALLOC_H_
#define MKITS_MCKITS_MLIBC_MCKITS_MALLOC_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Allocates dynamic memory, allocates size bytes and returns a pointer
  to the allocated memory. The memory is not initialized.
@notes: If failed, abort the program.
*/
void* mckits_malloc(size_t size);

/*
@brief: Allocates dynamic memory, allocates memory for an array of nmemb
  elements of size bytes each. The memory is set to zero.
@notes: If failed, abort the program.

mckits_calloc equal to:

```
void* ptr = malloc(nmemb * size);
memset(ptr, 0, nmemb * size);
```
*/
void* mckits_calloc(size_t nmemb, size_t size);

/*
@brief: Allocates dynamic memory, changes the size of the memory block pointed
  to by the ptr to size bytes.
@param ptr[in]: pointer to old memory buffer.
@param size[in]: new memory buffer size. new size can be smaller or larger than
  old memory buffer size.
@notes: If failed, abort the program.
*/
void* mckits_realloc(void* ptr, size_t size);

/*
@brief: Free dynamic memory.
*/
void mckits_free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
