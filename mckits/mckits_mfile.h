#ifndef MKITS_MCKITS_MCKITS_MFILE_H_
#define MKITS_MCKITS_MCKITS_MFILE_H_

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Read whole file to memory buffer.
@param pathname[in]: filename.
@param buf[out]: memory buffer used to store file content.
@param count[in]: memory buffer size.
@return
  On success, the number of bytes read is returned.
  On error, -1 is returned.
*/
ssize_t mckits_read_whole_file(const char* pathname, void* buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif
