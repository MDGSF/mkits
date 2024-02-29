#ifndef MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_FIXED_SIZE_STRING_H_
#define MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_FIXED_SIZE_STRING_H_

#include <cstring>
#include <string>

namespace mcppkits {
namespace mstl {

/*
@brief: Template class for non-malloc string. Will be truncated when assigned
  from a longer string.
*/
template <size_t MAX_CHARS>
struct fixed_string {
 public:
  static constexpr size_t max_size = MAX_CHARS;

  /*
  @brief: Default constructor.
  */
  fixed_string() noexcept {
    memset(data_, 0, sizeof(data_));
    len_ = 0;
  }

  /*
  @brief: Default copy constructor.
  */
  fixed_string(const fixed_string&) = default;

  /*
  @brief: Default copy assignment operator.
  */
  fixed_string& operator=(const fixed_string&) = default;

  /*
  @brief: Default move constructor.
  */
  fixed_string(fixed_string&&) = default;

  /*
  @brief: Default move assignment operator.
  */
  fixed_string& operator=(fixed_string&&) = default;

  /*
  @brief: Construct from a char array.
  */
  fixed_string(const char* c_array, size_t n_chars) noexcept {
    assign(c_array, n_chars);
  }

  fixed_string& assign(const char* c_array, size_t n_chars) noexcept {
    if (nullptr == c_array) {
      len_ = 0;
    } else {
      if (n_chars > MAX_CHARS) {
        len_ = MAX_CHARS;
      } else {
        len_ = n_chars;
      }
    }

    if (len_ > 0) {
      memcpy(data_, c_array, len_);
    }

    return *this;
  }

  /*
  @brief: Construct from a C string.
  */
  explicit fixed_string(const char* c_string) noexcept : fixed_string() {
    set(c_string != nullptr ? c_string : "");
  }

  /*
  @brief: Assign from a C string.
  */
  fixed_string& operator=(const char* c_string) noexcept {
    set(c_string != nullptr ? c_string : "");
    return *this;
  }

  /*
  @brief: Construct from a std::string.
  */
  explicit fixed_string(const std::string& str) noexcept : fixed_string() {
    set(str.c_str());
  }

  /*
  @brief: Assign from a std::string.
  */
  fixed_string& operator=(const std::string& str) noexcept {
    set(str.c_str());
    return *this;
  }

  /*
  @brief: Assign from fixed_string of any size.
  */
  template <size_t N>
  fixed_string& operator=(const fixed_string<N>& rhs) noexcept {
    set(rhs.c_str());
    return *this;
  }

  /*
  @brief: Get inner data pointer.
  */
  const char* c_str() const noexcept { return data_; }

  /*
  @brief: Clone to std::string.
  */
  std::string to_string() const { return std::string(data_); }

  /*
  @brief: Auto convert fixed_string to const char*.
  */
  operator const char*() const noexcept { return c_str(); }

  /*
  @brief: Get fixed_string size.
  */
  size_t size() const noexcept { return len_; }

  /*
  @brief: Equality compare to char*
  */
  bool operator==(const char* rhs) const noexcept {
    return strncmp(data_, rhs, MAX_CHARS) == 0;
  }

  /*
  @brief: Equality compare to std::string
  */
  bool operator==(const std::string& rhs) const noexcept {
    return strncmp(data_, rhs.c_str(), MAX_CHARS) == 0;
  }

  /*
  @brief: Equality compare to fixed_string
  */
  template <size_t N>
  bool operator==(const fixed_string<N>& rhs) const noexcept {
    return strncmp(data_, rhs.c_str(), MAX_CHARS) == 0;
  }

  /*
  @brief: Inequality compare to char*
  */
  bool operator!=(const char* rhs) const noexcept {
    return strncmp(data_, rhs, MAX_CHARS) != 0;
  }

  /*
  @brief: Inequality compare to std::string
  */
  bool operator!=(const std::string& rhs) const noexcept {
    return strncmp(data_, rhs.c_str(), MAX_CHARS) != 0;
  }

  /*
  @brief: Inequality compare to fixed_string
  */
  template <size_t N>
  bool operator!=(const fixed_string<N>& rhs) const noexcept {
    return strncmp(data_, rhs.c_str(), MAX_CHARS) != 0;
  }

  template <size_t N>
  bool operator<(const fixed_string<N>& rhs) const noexcept {
    return 0 > compare(rhs);
  }

  template <size_t N>
  bool operator>(const fixed_string<N>& rhs) const noexcept {
    return 0 < compare(rhs);
  }

  bool operator<(const std::string& rhs) const noexcept {
    return 0 > compare(rhs);
  }

  bool operator>(const std::string& rhs) const noexcept {
    return 0 < compare(rhs);
  }

  /*
  @brief: Compare with a C string.
  */
  int compare(const char* str) const noexcept {
    return strncmp(data_, str, MAX_CHARS);
  }

  /*
  @brief: Compare with a std::string.
  */
  int compare(const std::string& str) const noexcept {
    return strncmp(data_, str.c_str(), MAX_CHARS);
  }

  /*
  @brief: Compare with a fixed_string.
  */
  template <size_t N>
  int compare(const fixed_string<N>& str) const noexcept {
    return strncmp(data_, str.c_str(), MAX_CHARS);
  }

 private:
  void set(const char* c_string) noexcept {
    char* result =
        reinterpret_cast<char*>(memccpy(data_, c_string, '\0', MAX_CHARS));
    len_ = (result == nullptr) ? MAX_CHARS
                               : static_cast<size_t>(result - data_) - 1u;
  }

  // string data, including ending null character.
  char data_[MAX_CHARS + 1];
  // current string length, not include ending null character.
  size_t len_;
};

using string_255 = fixed_string<255>;

}  // namespace mstl
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_FIXED_SIZE_STRING_H_
