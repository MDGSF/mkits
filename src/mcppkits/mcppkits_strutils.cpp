#include "mcppkits/mcppkits_strutils.h"

#include <inttypes.h>
#include <wctype.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iterator>
#include <random>
#include <sstream>

namespace mcppkits {
namespace strutils {

std::string random_str(int size) {
  std::string result;
  result.resize(size);
  std::mt19937 rng(std::random_device{}());
  for (int i = 0; i < size; ++i) {
    result[i] = rng() % 0xFF;
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

std::string& str_to_lower(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), towlower);
  return str;
}

std::string str_to_lower(std::string&& str) {
  std::transform(str.begin(), str.end(), str.begin(), towlower);
  return std::move(str);
}

std::string& str_to_upper(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), towupper);
  return str;
}

std::string str_to_upper(std::string&& str) {
  std::transform(str.begin(), str.end(), str.begin(), towupper);
  return std::move(str);
}

#define TRIM(str, chars)                                      \
  do {                                                        \
    std::string m(0xFF, '\0');                                \
    for (auto& ch : chars) {                                  \
      m[(unsigned char&)ch] = '\1';                           \
    }                                                         \
    while (str.size() && m.at((unsigned char&)str.back())) {  \
      str.pop_back();                                         \
    }                                                         \
    while (str.size() && m.at((unsigned char&)str.front())) { \
      str.erase(0, 1);                                        \
    }                                                         \
  } while (0);

std::string& trim(std::string& str, const std::string& chars) {
  TRIM(str, chars);
  return str;
}

std::string trim(std::string&& str, const std::string& chars) {
  TRIM(str, chars);
  return std::move(str);
}

bool start_with(const std::string& str, const std::string& substr) {
  return str.find(substr) == 0;
}

bool end_with(const std::string& str, const std::string& substr) {
  auto pos = str.rfind(substr);
  return pos != std::string::npos && pos == str.size() - substr.size();
}

std::string int_to_string(int num) { return std::to_string(num); }
std::string int_to_string02(int num) {
  char buf[32];
  memset(buf, 0, sizeof buf);
  snprintf(buf, sizeof buf, "%d", num);
  return buf;
}

std::string int64_to_string(int64_t num) { return std::to_string(num); }
std::string int64_to_string02(int64_t num) {
  char buf[32];
  memset(buf, 0, sizeof buf);
  snprintf(buf, sizeof buf, "%" PRIi64, num);
  return buf;
}

int string_to_int(const std::string& str) { return std::stoi(str); }
int string_to_int02(const std::string& str) { return atoi(str.c_str()); }

int64_t string_to_int64(const std::string& str) { return std::stoll(str); }
int64_t string_to_int6402(const std::string& str) { return atoll(str.c_str()); }

std::string join_strings(const std::vector<std::string>& vec,
                         const std::string& sep) {
  std::ostringstream oss;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i > 0) {
      oss << sep;
    }
    oss << vec.at(i);
  }
  return oss.str();
}

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& sep) {
  std::vector<std::string> result;
  if (str.size() == 0) {
    return result;
  }

  if (sep.size() == 0) {
    for (size_t i = 0; i < str.size(); ++i) {
      result.push_back(str.substr(i, 1));
    }
    return result;
  }

  size_t pos = 0;
  while (true) {
    auto pos1 = str.find(sep, pos);
    if (pos1 == std::string::npos) {
      result.push_back(str.substr(pos));
      break;
    } else {
      result.push_back(str.substr(pos, pos1 - pos));
      pos = pos1 + sep.size();
    }
  }

  return result;
}

std::string merge_key_value_list(
    const std::vector<std::pair<std::string, std::string>>& vp,
    const std::string& entry_sep, const std::string& kv_sep) {
  std::vector<std::string> v;
  v.reserve(vp.size());
  std::transform(vp.begin(), vp.end(), std::back_inserter(v),
                 [&](const std::pair<std::string, std::string>& kv) {
                   return kv.first + kv_sep + kv.second;
                 });
  return join_strings(v, entry_sep);
}

std::vector<std::pair<std::string, std::string>> parse_key_value_list(
    const std::string& str, const std::string& entry_sep,
    const std::string& kv_sep) {
  std::vector<std::pair<std::string, std::string>> vp;
  auto entries = split_string(str, entry_sep);
  for (auto entry : entries) {
    if (entry.size() == 0) {
      continue;  // empty string
    }
    auto frags = split_string(entry, kv_sep);
    if (frags.size() == 2) {
      vp.push_back({frags[0], frags[1]});
    }
  }
  return vp;
}

}  // namespace strutils
}  // namespace mcppkits
