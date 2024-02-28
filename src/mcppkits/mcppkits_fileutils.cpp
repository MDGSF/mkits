#include "mcppkits/mcppkits_fileutils.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

namespace mcppkits {
namespace fileutils {

int read_whole_file(const std::string& filename, std::string& content) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Could not open file: " << filename << std::endl;
    return -1;
  }

  std::string file_content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
  content = file_content;
  file.close();
  return 0;
}

int write_to_file(const std::string& filename, const std::string& content) {
  std::ofstream file(filename, std::ios::out | std::ios::trunc);

  if (!file.is_open()) {
    return -1;
  }

  file << content;
  file.close();
  return 0;
}

int remove_file(const std::string& filename) {
  return std::remove(filename.c_str());
}

}  // namespace fileutils
}  // namespace mcppkits
