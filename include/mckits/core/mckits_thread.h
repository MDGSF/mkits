#ifndef MKITS_INCLUDE_MCKITS_CORE_MCKITS_THREAD_H_
#define MKITS_INCLUDE_MCKITS_CORE_MCKITS_THREAD_H_

#include <stddef.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: Set current thread name.
@notes: Maximum length of name is 16 bytes, include '\0'.
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

/*
@brief: Set current thread CPU affinity.
@param cpu_index_list[in]: CPU index array.
@param cpu_index_list_len[in]: length of CPU index array.
*/
void mckits_set_thread_cpu_affinity_list(const int* cpu_index_list,
                                         size_t cpu_index_list_len);

/*
@brief: Set current thread CPU affinity exclude.
@param cpu_index_list[in]: CPU index array will be exclude.
@param cpu_index_list_len[in]: length of CPU index array.
*/
void mckits_set_thread_cpu_affinity_list_except(const int* cpu_index_list,
                                                size_t cpu_index_list_len);

/*
@brief: Get current thread CPU affinity.
@param cpus[out]: CPU index array.
@param len[in]: cpus array size.
@return
  On success: the number of cpu index which has affinity with current thread.
  On error:
    -1: get affinity failed.
    -2: cpus array size is too small.
*/
ssize_t mckits_get_thread_cpu_affinity(int* cpus, size_t len);

#ifdef __cplusplus
}
#endif

#endif  // MKITS_INCLUDE_MCKITS_CORE_MCKITS_THREAD_H_
