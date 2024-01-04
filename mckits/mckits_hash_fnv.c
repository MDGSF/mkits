#include "mckits_hash_fnv.h"

uint32_t fnv_1_32(const uint8_t* data, size_t size) {
  static const uint32_t fnv_prime = 16777619U;
  static const uint32_t fnv_offset_basis = 2166136261U;
  uint32_t hash_value = fnv_offset_basis;
  for (int i = 0; i < size; ++i) {
    hash_value *= fnv_prime;
    hash_value ^= data[i];
  }
  return hash_value;
}

uint32_t fnv_1a_32(const uint8_t* data, size_t size) {
  static const uint32_t fnv_prime = 16777619U;
  static const uint32_t fnv_offset_basis = 2166136261U;
  uint32_t hash_value = fnv_offset_basis;
  for (int i = 0; i < size; ++i) {
    hash_value ^= data[i];
    hash_value *= fnv_prime;
  }
  return hash_value;
}

uint64_t fnv_1_64(const uint8_t* data, size_t size) {
  static const uint64_t fnv_prime = 1099511628211ULL;
  static const uint64_t fnv_offset_basis = 14695981039346656037ULL;
  uint64_t hash_value = fnv_offset_basis;
  for (int i = 0; i < size; ++i) {
    hash_value *= fnv_prime;
    hash_value ^= data[i];
  }
  return hash_value;
}

uint64_t fnv_1a_64(const uint8_t* data, size_t size) {
  static const uint64_t fnv_prime = 1099511628211ULL;
  static const uint64_t fnv_offset_basis = 14695981039346656037ULL;
  uint64_t hash_value = fnv_offset_basis;
  for (int i = 0; i < size; ++i) {
    hash_value ^= data[i];
    hash_value *= fnv_prime;
  }
  return hash_value;
}
