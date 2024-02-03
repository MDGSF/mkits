#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_STRUTILS_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_STRUTILS_H_

#include <string>
#include <utility>
#include <vector>

namespace mcppkits {
namespace strutils {

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
@brief: Change string character to lower.
@param str[in]: The reference of string.
@return: The reference of input str.
*/
std::string& str_to_lower(std::string& str);

/*
@brief: Change string character to lower.
@param str[in]: Move string into function.
@return: Move string out from function.
*/
std::string str_to_lower(std::string&& str);

/*
@brief: Change string character to upper.
@param str[in]: The reference of string.
@return: The reference of input str.
*/
std::string& str_to_upper(std::string& str);

/*
@brief: Change string character to upper.
@param str[in]: Move string into function.
@return: Move string out from function.
*/
std::string str_to_upper(std::string&& str);

/*
@brief: Trim string start and end chars.
@param str[in]: The reference of string.
@param chars[in]: Characters will be trimmed.
@return: The reference of input str.
*/
std::string& trim(std::string& str, const std::string& chars = " \r\n\t");

/*
@brief: Trim string start and end chars.
@param str[in]: Move string into function.
@param chars[in]: Characters will be trimmed.
@return: Move trimmed string out from function.
*/
std::string trim(std::string&& str, const std::string& chars = " \r\n\t");

/*
@brief: Check whether substr is prefix of str.
*/
bool start_with(const std::string& str, const std::string& substr);

/*
@brief: Check whether substr is suffix of str.
*/
bool end_with(const std::string& str, const std::string& substr);

/*
@brief: Convert int to std::string.
*/
std::string int_to_string(int num);
std::string int_to_string02(int num);

/*
@brief: Convert int64_t to std::string.
*/
std::string int64_to_string(int64_t num);
std::string int64_to_string02(int64_t num);

/*
@brief: Convert std::string to int.
*/
int string_to_int(const std::string& str);
int string_to_int02(const std::string& str);

/*
@brief: Convert std::string to int64_t.
*/
int64_t string_to_int64(const std::string& str);
int64_t string_to_int6402(const std::string& str);

/*
@brief: Join vector string, use sep as separator.
@example:
  vec = ["hello", "hi", "Bye"]; sep = ":";
  return = "hello:hi:Bye"
*/
std::string join_strings(const std::vector<std::string>& vec,
                         const std::string& sep);

/*
@brief: Split string, use sep as separator.
@example:
  str="",      sep=","  --> result = []
  str="hello", sep=""   --> result = ["h", "e", "l", "l", "o"]
  str="hello:hi:Bye", sep=":" --> result = ["hello", "hi", "Bye"]
*/
std::vector<std::string> split_string(const std::string& str,
                                      const std::string& sep);

/*
@brief: Join vector pair<string, string>.
@example:
  vp=[("name", "alice"), ("age", "18"), ("sex", "female")]
  entry_sep=","
  kv_sep=":"
  return="name:alice,age:18,sex:female"
*/
std::string merge_key_value_list(
    const std::vector<std::pair<std::string, std::string>>& vp,
    const std::string& entry_sep, const std::string& kv_sep);

/*
@brief: Parse key value list string
@example:
  str="name:alice,age:18,sex:female"
  entry_sep=","
  kv_sep=":"
  return=[("name", "alice"), ("age", "18"), ("sex", "female")]
*/
std::vector<std::pair<std::string, std::string>> parse_key_value_list(
    const std::string& str, const std::string& entry_sep,
    const std::string& kv_sep);

}  // namespace strutils
}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_STRUTILS_H_
