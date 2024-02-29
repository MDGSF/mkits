#ifndef MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_SINGLETON_H_
#define MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_SINGLETON_H_

namespace mcppkits {

template <typename T>
class Singleton {
 public:
  static T& Instance() {
    static T instance;
    return instance;
  }

 private:
  Singleton() = default;
  ~Singleton() = default;
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_SINGLETON_H_
