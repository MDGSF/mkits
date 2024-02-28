#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_RANDOM_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_RANDOM_H_

#include <string>
#include <vector>

namespace mcppkits {

/*
@brief: Generate random bytes, every byte is 0~255.
@param size[in]: Random bytes length.
@return: Random bytes.
*/
std::vector<uint8_t> random_bytes(int size);

/*
@brief: Generate random string, every byte is 0~255.
@param size[in]: Random string length.
@return: Random string.
*/
std::string random_str(int size);

/*
@brief: Generate random string, every byte is 0~9 a-z A-Z.
@param size[in]: Random string length.
@return: Random string.
*/
std::string random_str_alnum(int size);

/*
@brief: Generate random string, every byte is a-z A-Z.
@param size[in]: Random string length.
@return: Random string.
*/
std::string random_str_alpha(int size);

/*
@brief: Generate a temp filename. /tmp/xxx
@param filename_size[in]: filename length.
@return: Temp filename.
*/
std::string random_tmp_filename(int filename_size = 8);

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_RANDOM_H_
