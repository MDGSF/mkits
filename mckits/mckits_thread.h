#ifndef MKITS_MCKITS_MCKITS_THREAD_H_
#define MKITS_MCKITS_MCKITS_THREAD_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Set current thread name.
*/
void mckits_set_thread_name(const char* name);

/*
@brief: Get current thread name.
*/
void mckits_get_thread_name(char* name, size_t len);

/*
@brief: Set current thread CPU affinity.
@param cpu_index[in]: CPU index.
*/
void mckits_set_thread_cpu_affinity(int cpu_index);

#ifdef __cplusplus
}
#endif

#endif
