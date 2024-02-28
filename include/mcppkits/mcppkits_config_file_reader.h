#ifndef MKITS_INCLUDE_MCPPKITS_MCPPKITS_CONFIG_FILE_READER_H_
#define MKITS_INCLUDE_MCPPKITS_MCPPKITS_CONFIG_FILE_READER_H_

#include <map>
#include <string>

namespace mcppkits {

/*
name1 = value1
name2 = value2
*/
class ConfigFileReader {
 public:
  ConfigFileReader() = default;
  ~ConfigFileReader() = default;

  ConfigFileReader(const ConfigFileReader&) = default;
  ConfigFileReader& operator=(const ConfigFileReader&) = default;

  ConfigFileReader(ConfigFileReader&&) = default;
  ConfigFileReader& operator=(ConfigFileReader&&) = default;

  /*
  @brief: Load config from file.
  return: On success, 0 is returned. Else means failed.
  */
  int load_file(const std::string& filename);

  /*
  @brief: Get value by name.
  @param name[in]: entry name.
  @return: entry value. If not found, return empty string.
  */
  std::string get(const std::string& name);

  /*
  @brief: Set name = value to memory and file.
  @param name[in]: entry name.
  @param value[in]: entry value.
  return: On success, 0 is returned. Else means failed.
  */
  int set(const std::string& name, const std::string& value);

 private:
  int write_file(const std::string& filename);
  std::string to_string();

  std::string config_file_{};
  std::map<std::string, std::string> config_map_{};
};

}  // namespace mcppkits

#endif  // MKITS_INCLUDE_MCPPKITS_MCPPKITS_CONFIG_FILE_READER_H_
