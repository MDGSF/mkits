#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETON_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETON_H_

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
  Singleton(const Singleton&) = default;
  Singleton& operator=(const Singleton&) = default;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_SINGLETON_H_
