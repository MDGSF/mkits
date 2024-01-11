#ifndef MKITS_MCKITS_CORE_MCKITS_RAWPIPE_H_
#define MKITS_MCKITS_CORE_MCKITS_RAWPIPE_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Create a pipe. It will have two file descriptor.
  pipe_fd_[0]: read fd. Default is non-blocking.
  pipe_fd_[1]: write fd. Default is blocking.
*/
struct MckitsRawPipe {
  int pipe_fd_[2];
};

/*
@brief: Creat a new pipe.
*/
struct MckitsRawPipe* mckits_rawpipe_new();

/*
@brief: Close the pipe read and write fd, and free memory.
*/
void mckits_rawpipe_drop(struct MckitsRawPipe* rawpipe);

/*
@brief: Close old pipe, and create new pipe.
*/
void mckits_rawpipe_reopen(struct MckitsRawPipe* rawpipe);

/*
@brief: Get pipe read fd.
*/
int mckits_rawpipe_read_fd(struct MckitsRawPipe* rawpipe);

/*
@brief: Get pipe write fd.
*/
int mckits_rawpipe_write_fd(struct MckitsRawPipe* rawpipe);

/*
@brief: Write data to pipe_fd_[1].
@param buf[in]: Buffer store data will be write.
@param count[in]: Size of buffer.
@return:
  On success, the number of bytes written is returned.
  On error, -1 is returned.
*/
int mckits_rawpipe_write(struct MckitsRawPipe* rawpipe, const void* buf,
                         size_t count);

/*
@brief: Read data from pipe_fd_[0].
@param buf[out]: Buffer used to store readed data.
@param count[in]: Size of buffer.
@return:
  On success, the number of bytes read is returned.
  On error, -1 is returned.
*/
int mckits_rawpipe_read(struct MckitsRawPipe* rawpipe, void* buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif
