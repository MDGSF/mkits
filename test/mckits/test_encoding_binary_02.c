#include <assert.h>
#include <stdio.h>

#include "mckits/core/mckits_mtime.h"
#include "mckits/mstl/encoding/mckits_encoding_binary.h"

struct MessageHeader {
  uint8_t magic_word[4];
  uint16_t version;
  uint16_t msg_type;
  uint32_t metadata_offset;
  uint32_t metadata_length;
  uint32_t payload_offset;
  uint32_t payload_length;
};

int is_message_header_equal(const struct MessageHeader* msg_header_01,
                            const struct MessageHeader* msg_header_02) {
  return msg_header_01->magic_word[0] == msg_header_02->magic_word[0] &&
         msg_header_01->magic_word[1] == msg_header_02->magic_word[1] &&
         msg_header_01->magic_word[2] == msg_header_02->magic_word[2] &&
         msg_header_01->magic_word[3] == msg_header_02->magic_word[3] &&
         msg_header_01->version == msg_header_02->version &&
         msg_header_01->msg_type == msg_header_02->msg_type &&
         msg_header_01->metadata_offset == msg_header_02->metadata_offset &&
         msg_header_01->metadata_length == msg_header_02->metadata_length &&
         msg_header_01->payload_offset == msg_header_02->payload_offset &&
         msg_header_01->payload_length == msg_header_02->payload_length;
}

void message_header_encode(const struct MessageHeader* msg_header,
                           uint8_t* buf) {
  uint8_t* p = buf;

  *p++ = msg_header->magic_word[0];
  *p++ = msg_header->magic_word[1];
  *p++ = msg_header->magic_word[2];
  *p++ = msg_header->magic_word[3];

  mckits_big_endian_encode_u16(msg_header->version, p);
  p += 2;

  mckits_big_endian_encode_u16(msg_header->msg_type, p);
  p += 2;

  mckits_big_endian_encode_u32(msg_header->metadata_offset, p);
  p += 4;

  mckits_big_endian_encode_u32(msg_header->metadata_length, p);
  p += 4;

  mckits_big_endian_encode_u32(msg_header->payload_offset, p);
  p += 4;

  mckits_big_endian_encode_u32(msg_header->payload_length, p);
  p += 4;
}

void message_header_decode(struct MessageHeader* msg_header,
                           const uint8_t* buf) {
  const uint8_t* p = buf;

  msg_header->magic_word[0] = *p++;
  msg_header->magic_word[1] = *p++;
  msg_header->magic_word[2] = *p++;
  msg_header->magic_word[3] = *p++;

  msg_header->version = mckits_big_endian_decode_u16(p);
  p += 2;

  msg_header->msg_type = mckits_big_endian_decode_u16(p);
  p += 2;

  msg_header->metadata_offset = mckits_big_endian_decode_u32(p);
  p += 4;

  msg_header->metadata_length = mckits_big_endian_decode_u32(p);
  p += 4;

  msg_header->payload_offset = mckits_big_endian_decode_u32(p);
  p += 4;

  msg_header->payload_length = mckits_big_endian_decode_u32(p);
  p += 4;
}

void test_message_header_encode_decode() {
  struct MessageHeader msg_header;
  msg_header.magic_word[0] = 'm';
  msg_header.magic_word[1] = 'k';
  msg_header.magic_word[2] = 'i';
  msg_header.magic_word[3] = 't';
  msg_header.version = 0x0001;
  msg_header.msg_type = 0x0001;
  msg_header.metadata_offset = 123;
  msg_header.metadata_length = 456;
  msg_header.payload_offset = 789;
  msg_header.payload_length = 321;

  uint8_t buf[4096] = {0};
  message_header_encode(&msg_header, buf);

  struct MessageHeader msg_header_decoded;
  message_header_decode(&msg_header_decoded, buf);

  assert(is_message_header_equal(&msg_header, &msg_header_decoded) == 1);

  for (int i = 0; i < 24; ++i) {
    printf("%02X ", buf[i]);
  }
  printf("\n");
}

void bench_encode_message_header() {
  struct MessageHeader msg_header;
  msg_header.magic_word[0] = 'm';
  msg_header.magic_word[1] = 'k';
  msg_header.magic_word[2] = 'i';
  msg_header.magic_word[3] = 't';
  msg_header.version = 0x0001;
  msg_header.msg_type = 0x0001;
  msg_header.metadata_offset = 123;
  msg_header.metadata_length = 456;
  msg_header.payload_offset = 789;
  msg_header.payload_length = 321;

  uint8_t buf[4096] = {0};

  int64_t count = 100000000;
  int64_t start = mckits_current_clock_nanoseconds();
  for (int64_t i = 0; i < count; ++i) {
    message_header_encode(&msg_header, buf);
  }
  int64_t end = mckits_current_clock_nanoseconds();
  int64_t diff = end - start;
  printf(
      "message header encode diff: %ld ns, count: %ld, %.2lf ns/count, %.2lf "
      "count/s\n",
      diff, count, (double)diff / (double)count,
      (double)count / ((double)diff / 1000000000));
}

int main() {
  test_message_header_encode_decode();
  bench_encode_message_header();
  return 0;
}
