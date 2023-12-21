#ifndef MKITS_MCKITS_MCKITS_MOS_H_
#define MKITS_MCKITS_MCKITS_MOS_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Get current working directory.
@param buf[out]: memory buffer used to store working directory.
@param size[in]: memory buffer size.
@return:
  On success, return a pointer to buf.
  On error, return NULL.
*/
char* mckits_working_directory(char* buf, size_t size);

#ifdef __cplusplus
}
#endif

#endif
