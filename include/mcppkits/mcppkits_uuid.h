#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_

#include <string>

namespace mcppkits {

class UUIDGenerator {
 public:
  /*
  @brief: Generate a new uuid.
  @return: new uuid.
  */
  static std::string uuid();

 private:
  UUIDGenerator() = delete;
  ~UUIDGenerator() = delete;
  UUIDGenerator(const UUIDGenerator&) = delete;
  UUIDGenerator& operator=(const UUIDGenerator&) = delete;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_
