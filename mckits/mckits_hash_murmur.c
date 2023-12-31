#include "mckits_hash_murmur.h"

uint32_t mckits_murmur3_32(const uint8_t* data, size_t len, uint32_t seed) {
  uint32_t k = 0;
  uint32_t h = seed;
  size_t left_len = len;

  // four byte chunk
  while (left_len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;

    h ^= k;
    h = (h << 13) | (h >> 19);
    h = h * 5 + 0xe6546b64;

    data += 4;
    left_len -= 4;
  }

  // remaining bytes
  k = 0;
  switch (left_len) {
    case 3:
      k ^= data[2] << 16;
      /* fall through */
    case 2:
      k ^= data[1] << 8;
      /* fall through */
    case 1:
      k ^= data[0];
  }
  k *= 0xcc9e2d51;
  k = (k << 15) | (k >> 17);
  k *= 0x1b873593;
  h ^= k;

  // Finalize.
  h ^= len;
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

uint32_t mckits_murmur2_32(const uint8_t* data, size_t len) {
  uint32_t k = 0;
  uint32_t h = 0 ^ len;

  while (len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= 0x5bd1e995;
    k ^= k >> 24;
    k *= 0x5bd1e995;

    h *= 0x5bd1e995;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len) {
    case 3:
      h ^= data[2] << 16;
      /* fall through */
    case 2:
      h ^= data[1] << 8;
      /* fall through */
    case 1:
      h ^= data[0];
      h *= 0x5bd1e995;
  }

  h ^= h >> 13;
  h *= 0x5bd1e995;
  h ^= h >> 15;

  return h;
}
