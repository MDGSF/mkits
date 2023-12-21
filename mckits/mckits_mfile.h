#ifndef MKITS_MCKITS_MCKITS_MFILE_H_
#define MKITS_MCKITS_MCKITS_MFILE_H_

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Check file exists or not.
@param pathname[in]: filename.
@return:
  1: file exists.
  0: file not exists.
*/
int mckits_is_file_exists(const char* pathname);

/*
@brief: Check directory exists or not.
@param pathname[in]: directory pathname.
@return:
  1: directory exists.
  0: directory not exists.
*/
int mckits_is_dir_exists(const char* pathname);

/*
@brief: Get file size in bytes.
@param pathname[in]: filename.
@return:
  On success, file size in bytes.
  On error, -1 is returned
*/
ssize_t mckits_file_size(const char* pathname);

/*
@brief: Remove file from filesystem.
@param pathname[in]: filename.
*/
void mckits_remove_file(const char* pathname);

/*
@brief: Delete the directory recursively.
@param pathname[in]: directory pathname.
*/
void mckits_remove_dir(const char* pathname);

/*
@brief: Create the directory recursively.
@param pathname[in]: directory pathname.
*/
void mckits_mkdir_all(const char* pathname);

/*
@brief: Return all but the last element of pathname
@param pathname[in]: pathname.
@param dirpath[out]: buffer used to save directory.
@param count[in]: dirpath buffer size.
@return
  On success, dirpath string size.
  On error, -1 mean count is to small.
*/
ssize_t mckits_path_dir(const char* pathname, char* dirpath, size_t count);

/*
@brief: Return the last element of pathname
@param pathname[in]: pathname.
@param basename[out]: buffer used to save the last element.
@param count[in]: basename buffer size.
@return
  On success, basename string size.
  On error, -1 mean count is to small.
*/
ssize_t mckits_path_base(const char* pathname, char* basename, size_t count);

/*
@brief: Read whole file to memory buffer.
@param pathname[in]: filename.
@param buf[out]: memory buffer used to store file content.
@param count[in]: memory buffer size.
@return
  On success, the number of bytes read is returned.
  On error,
    -1: open file failed.
    -2: ftell get file size failed.
    -3: file_size > count, file size is greater than buffer size.
    -4: readed bytes not equal to file size.
*/
ssize_t mckits_read_whole_file(const char* pathname, void* buf, size_t count);

/*
@brief: Write memory buffer to file.
@param pathname[in]: filename.
@param buf[in]: memory buffer will be write to file.
@param count[in]: memory buffer size.
@return
  On success, the number of bytes written is returned.
  On error,
    -1: open file failed.
*/
ssize_t mckits_write_to_file(const char* pathname, const void* buf,
                             size_t count);

#ifdef __cplusplus
}
#endif

#endif
