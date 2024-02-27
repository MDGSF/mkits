#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_RAII_WRAPPER_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_RAII_WRAPPER_H_

namespace mcppkits {

template <typename T>
class RAIIWrapper {
 public:
  RAIIWrapper(T* p) : ptr(p) {}

  virtual ~RAIIWrapper() {
    if (ptr != nullptr) {
      delete ptr;
      ptr = nullptr;
    }
  }

  RAIIWrapper(const RAIIWrapper&) = delete;
  RAIIWrapper& operator=(const RAIIWrapper&) = delete;

  RAIIWrapper(RAIIWrapper&&) = default;
  RAIIWrapper& operator=(RAIIWrapper&&) = default;

  T* operator->() { return ptr; }
  T& operator*() { return *ptr; }

 private:
  T* ptr;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_RAII_WRAPPER_H_
