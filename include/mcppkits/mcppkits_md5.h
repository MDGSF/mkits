// Inspired by flamingo/MD5.h
#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_MD5_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_MD5_H_

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>

namespace mcppkits {

class MD5 {
 public:
  MD5();
  MD5(const void* data, size_t length);
  MD5(const std::string& str);
  MD5(std::ifstream& in);

  /*
  @brief: Update data to MD5 calculator. This can be called multi-times.
  @param data[in]: Input binary data.
  @param length[in]: data length in bytes.
  */
  void update(const void* data, size_t length);
  void update(const std::string& str);
  void update(std::ifstream& in);

  /*
  @brief: Get MD5 digest. Pointer to inner memory buffer, no need to free.
  */
  const uint8_t* digest();

  /*
  @brief: Get MD5 digest string.
  */
  std::string to_string();

  /*
  @brief: Reset the calculate state.
  */
  void reset();

  /*
  @brief: Disable copy constructor.
  */
  MD5(const MD5&) = delete;

  /*
  @brief: Disable copy assignment operator.
  */
  MD5& operator=(const MD5&) = delete;

  /*
  @brief: Default move constructor.
  */
  MD5(MD5&&) = default;

  /*
  @brief: Default move assignment operator.
  */
  MD5& operator=(MD5&&) = default;

 private:
  void update(const uint8_t* data, size_t length);
  void transform(const uint8_t block[64]);
  void encode(const uint32_t* input, uint8_t* output, size_t length);
  void decode(const uint8_t* input, uint32_t* output, size_t length);
  void end();
  std::string bytes_to_hex_string(const uint8_t* input, size_t length);

 private:
  uint32_t state_[4];  // state (ABCD)
  uint32_t count_[2];
  uint8_t buffer_[64];
  uint8_t digest_[16];
  bool finished_;

  static const uint8_t PADDING[64];
  static const char HEX[16];
  enum { BUFFER_SIZE = 1024 };
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_MD5_H_
