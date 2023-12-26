#ifndef MKITS_MCKITS_MCKITS_MOS_H_
#define MKITS_MCKITS_MCKITS_MOS_H_

#include <stddef.h>
#include <sys/types.h>

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

/*
@brief: Change current working directory.
@param pathname[in]: new working directory.
@return:
  On success, zero is returned.
  On error, -1 is returned.
*/
int mckits_change_working_directory(const char* pathname);

/*
@brief: Get executable path.
@param buf[out]: memory buffer used to store executable path.
@param bufsiz[in]: memory buffer size.
@return:
  On success, the number of bytes placed in buf.
  On error, -1 is returned.
*/
ssize_t mckits_exe_path(char* buf, size_t bufsiz);
ssize_t mckits_exe_path_dir(char* buf, size_t bufsiz);
ssize_t mckits_exe_path_base(char* buf, size_t bufsiz);

/*
@brief: Get hardware core number.
*/
int mckits_hardware_concurrency();

#ifdef __cplusplus
}
#endif

#endif
