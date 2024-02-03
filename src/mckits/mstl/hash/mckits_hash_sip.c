#include "mckits/mstl/hash/mckits_hash_sip.h"

static inline void little_endian_encode_u64(uint64_t v, uint8_t *b) {
  b[0] = (uint8_t)(v);
  b[1] = (uint8_t)(v >> 8);
  b[2] = (uint8_t)(v >> 16);
  b[3] = (uint8_t)(v >> 24);
  b[4] = (uint8_t)(v >> 32);
  b[5] = (uint8_t)(v >> 40);
  b[6] = (uint8_t)(v >> 48);
  b[7] = (uint8_t)(v >> 56);
}

static inline uint64_t little_endian_decode_u64(const uint8_t *b) {
  return (uint64_t)(b[0]) | ((uint64_t)(b[1]) << 8) | ((uint64_t)(b[2]) << 16) |
         ((uint64_t)(b[3]) << 24) | ((uint64_t)(b[4]) << 32) |
         ((uint64_t)(b[5]) << 40) | ((uint64_t)(b[6]) << 48) |
         ((uint64_t)(b[7]) << 56);
}

//-----------------------------------------------------------------------------
// SipHash reference C implementation
//
// Copyright (c) 2012-2016 Jean-Philippe Aumasson
// <jeanphilippe.aumasson@gmail.com>
// Copyright (c) 2012-2014 Daniel J. Bernstein <djb@cr.yp.to>
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along
// with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
//
// default: SipHash-2-4
//-----------------------------------------------------------------------------
static uint64_t sip64(const uint8_t *in, const size_t inlen, uint64_t seed0,
                      uint64_t seed1) {
#define ROTL(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))
#define SIPROUND       \
  {                    \
    v0 += v1;          \
    v1 = ROTL(v1, 13); \
    v1 ^= v0;          \
    v0 = ROTL(v0, 32); \
    v2 += v3;          \
    v3 = ROTL(v3, 16); \
    v3 ^= v2;          \
    v0 += v3;          \
    v3 = ROTL(v3, 21); \
    v3 ^= v0;          \
    v2 += v1;          \
    v1 = ROTL(v1, 17); \
    v1 ^= v2;          \
    v2 = ROTL(v2, 32); \
  }
  uint64_t k0 = little_endian_decode_u64((const uint8_t *)&seed0);
  uint64_t k1 = little_endian_decode_u64((const uint8_t *)&seed1);
  uint64_t v3 = UINT64_C(0x7465646279746573) ^ k1;
  uint64_t v2 = UINT64_C(0x6c7967656e657261) ^ k0;
  uint64_t v1 = UINT64_C(0x646f72616e646f6d) ^ k1;
  uint64_t v0 = UINT64_C(0x736f6d6570736575) ^ k0;
  const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
  for (; in != end; in += 8) {
    uint64_t m = little_endian_decode_u64(in);
    v3 ^= m;
    SIPROUND;
    SIPROUND;
    v0 ^= m;
  }
  const int left = inlen & 7;
  uint64_t b = ((uint64_t)inlen) << 56;
  switch (left) {
    case 7:
      b |= ((uint64_t)in[6]) << 48; /* fall through */
    case 6:
      b |= ((uint64_t)in[5]) << 40; /* fall through */
    case 5:
      b |= ((uint64_t)in[4]) << 32; /* fall through */
    case 4:
      b |= ((uint64_t)in[3]) << 24; /* fall through */
    case 3:
      b |= ((uint64_t)in[2]) << 16; /* fall through */
    case 2:
      b |= ((uint64_t)in[1]) << 8; /* fall through */
    case 1:
      b |= ((uint64_t)in[0]);
      break;
    case 0:
      break;
  }
  v3 ^= b;
  SIPROUND;
  SIPROUND;
  v0 ^= b;
  v2 ^= 0xff;
  SIPROUND;
  SIPROUND;
  SIPROUND;
  SIPROUND;
  b = v0 ^ v1 ^ v2 ^ v3;
  uint64_t out = 0;
  little_endian_encode_u64(b, (uint8_t *)&out);
  return out;
}

uint64_t mckits_hash_sip(const uint8_t *data, size_t len, uint64_t seed0,
                         uint64_t seed1) {
  return sip64(data, len, seed0, seed1);
}
