#include "mcppkits/mcppkits_random.h"

#include <random>

namespace mcppkits {

std::vector<uint8_t> random_bytes(int size) {
  std::vector<uint8_t> result;
  result.resize(size);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < size; ++i) {
    result[i] = static_cast<uint8_t>(rng() % 0xFF);
  }
  return result;
}

std::string random_str(int size) {
  std::string result;
  result.resize(size);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < size; ++i) {
    result[i] = static_cast<char>(rng() % 0xFF);
  }
  return result;
}

std::string random_str_alnum(int size) {
  static const char Chars[] =
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string result;
  result.resize(size);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < size; ++i) {
    uint32_t x = rng() % (sizeof(Chars) - 1);
    result[i] = Chars[x];
  }
  return result;
}

std::string random_str_alpha(int size) {
  static const char Chars[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::string result;
  result.resize(size);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < size; ++i) {
    uint32_t x = rng() % (sizeof(Chars) - 1);
    result[i] = Chars[x];
  }
  return result;
}

std::string random_tmp_filename(int filename_size) {
  std::string filename = random_str_alpha(filename_size);
  return "/tmp/" + filename;
}

}  // namespace mcppkits
