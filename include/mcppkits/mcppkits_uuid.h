/*
@brief: rfc4122-A Universally Unique IDentifier (UUID) URN Namespace
*/

#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_

#include <string>

namespace mcppkits {

class UUIDGenerator {
 public:
  /*
  @brief: Generate a new uuid. UUIDv4.
  @return: new uuid.
  */
  static std::string uuid();

 private:
  UUIDGenerator() = delete;
  ~UUIDGenerator() = delete;

  UUIDGenerator(const UUIDGenerator&) = delete;
  UUIDGenerator& operator=(const UUIDGenerator&) = delete;

  UUIDGenerator(UUIDGenerator&&) = delete;
  UUIDGenerator& operator=(UUIDGenerator&&) = delete;
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_UUID_H_
