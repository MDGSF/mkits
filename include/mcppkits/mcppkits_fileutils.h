#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_

#include <string>

namespace mcppkits {
namespace fileutils {

/*
@biref: Read whole file.
@param filename[in]: File will be read.
@return: File content. If read failed, return an empty string.
*/
std::string read_whole_file(const std::string& filename);

/*
@brief: Write content to file.
@param filename[in]: File will be write.
@param content[in]: Content data will be write to file.
@return: On success, 0 is returned. Else means failed.
*/
int write_to_file(const std::string& filename, const std::string& content);

/*
@brief: Remove file.
@return: On success, 0 is returned. Else means failed.
*/
int remove_file(const std::string& filename);

}  // namespace fileutils
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_FILEUTILS_H_
