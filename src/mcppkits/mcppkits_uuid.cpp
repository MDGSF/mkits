#include "mcppkits/mcppkits_uuid.h"

#include <iostream>
#include <random>
#include <sstream>
#include <string>

namespace mcppkits {

std::string UUIDGenerator::uuid() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(0, 15);

  const char *hex = "0123456789abcdef";
  std::stringstream ss;
  for (int i = 0; i < 36; ++i) {
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      ss << "-";
    } else if (i == 14) {
      ss << "4";
    } else if (i == 19) {
      ss << hex[(dis(gen) & 0x3) | 0x8];
    } else {
      ss << hex[dis(gen)];
    }
  }

  return ss.str();
}

}  // namespace mcppkits
