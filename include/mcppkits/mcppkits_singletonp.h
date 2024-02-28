#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETONP_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETONP_H_

#include <cstdlib>
#include <mutex>
#include <thread>

namespace mcppkits {

template <typename T>
class SingletonP {
 public:
  static T& Instance() {
    if (instance_ == nullptr) {
      std::lock_guard<std::mutex> lock(mtx_);
      if (instance_ == nullptr) {
        instance_ = new T();
        ::atexit(destroy);
      }
    }
    return *instance_;
  }

 private:
  SingletonP() = default;
  ~SingletonP() = default;
  SingletonP(const SingletonP&) = delete;
  SingletonP& operator=(const SingletonP&) = delete;
  SingletonP(SingletonP&&) = delete;
  SingletonP& operator=(SingletonP&&) = delete;
  static void destroy() { delete instance_; }
  static T* instance_;
  static std::mutex mtx_;
};

template <typename T>
T* SingletonP<T>::instance_ = nullptr;

template <typename T>
std::mutex SingletonP<T>::mtx_;

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETONP_H_
