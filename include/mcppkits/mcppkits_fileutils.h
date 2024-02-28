#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_

#include <string>

namespace mcppkits {
namespace fileutils {

std::string read_whole_file(const std::string& filename);

int write_to_file(const std::string& filename, const std::string& content);

}  // namespace fileutils
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_
