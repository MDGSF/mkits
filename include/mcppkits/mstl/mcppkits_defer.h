#ifndef MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_DEFER_H_
#define MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_DEFER_H_

#include <functional>

namespace mcppkits {

/*
@brief: Defer like golang defer keyword.
@example:

void test() {
  DEFER([]() { std::cout << "Deferred executed 2" << std::endl; })
  DEFER([]() { std::cout << "Deferred executed 1" << std::endl; })
  std::cout << "Some actions..." << std::endl;
}

test() function output:
Some actions...
Deferred executed 1
Deferred executed 2
*/
class Defer final {
 public:
  Defer() = delete;
  explicit Defer(std::function<void()> func) : func(func) {}
  ~Defer() { func(); }

  Defer(const Defer&) = delete;
  Defer& operator=(const Defer&) = delete;

  Defer(Defer&&) = delete;
  Defer& operator=(Defer&&) = delete;

 private:
  std::function<void()> func;
};

}  // namespace mcppkits

#define mcppkits_Defer_CONCAT_INTERNAL(x, y) x##y
#define mcppkits_Defer_CONCAT(x, y) mcppkits_Defer_CONCAT_INTERNAL(x, y)

/*
@brief: This macro is public, you should use this macro.
it will expand like:
  Defer _mcppkits_defer_[line_number]([]() { xxx });
  `_mcppkits_defer_[line_number]` is an Defer instance.
*/
#define DEFER(func) \
  mcppkits::Defer mcppkits_Defer_CONCAT(_mcppkits_defer_, __LINE__)(func)

#endif  // MKITS_INCLUDE_MCPPKITS_MSTL_MCPPKITS_DEFER_H_
