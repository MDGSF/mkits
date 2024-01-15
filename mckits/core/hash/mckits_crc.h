#ifndef MKITS_MCKITS_CORE_MCKITS_CRC_H_
#define MKITS_MCKITS_CORE_MCKITS_CRC_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
@brief: (32-bit crc16) Calculate data crc code.
@param data[in]: Input data.
@param size[in]: data size in byte.
*/
static inline uint32_t mckits_crc(const uint8_t* data, size_t size) {
  uint32_t sum = 0;
  for (; size > 0; --size) {
    sum = sum >> 1 | sum << 31;
    sum += *data++;
  }
  return sum;
}

#ifdef __cplusplus
}
#endif

#endif
