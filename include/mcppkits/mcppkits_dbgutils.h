#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_DBGUTILS_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_DBGUTILS_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace mcppkits {

template <typename T>
void PrintVec01(const std::vector<T> vec, const std::string& name) {
  int i = 0;
  std::cerr << "vector: " << name << ", size: " << vec.size() << std::endl;
  for (const T& entry : vec) {
    std::cerr << "vec[" << i++ << "]: " << entry << std::endl;
  }
}

template <typename T>
void PrintVec02(const std::vector<T>& vec, const std::string& name) {
  int i = 0;
  std::cout << "vector: " << name << ", size: " << vec.size() << std::endl;
  std::cout << "[";
  for (auto v : vec) {
    if (i > 0) {
      std::cout << ", ";
    }
    std::cout << v;
    ++i;
  }
  std::cout << "]" << std::endl;
}

template <typename KeyType, typename ValType>
void PrintMap(const std::map<KeyType, ValType>& m) {
  int i = 0;
  std::cout << "{";
  for (auto kv : m) {
    if (i > 0) {
      std::cout << ", ";
    }

    std::cout << kv.first << ": " << kv.second;
    ++i;
  }
  std::cout << "}" << std::endl;
}

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_DBGUTILS_H_
