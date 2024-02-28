#include "mcppkits/mcppkits_config_file_reader.h"

#include <iostream>
#include <sstream>

#include "mcppkits/mcppkits_fileutils.h"
#include "mcppkits/mcppkits_strutils.h"

namespace mcppkits {

ConfigFileReader::ConfigFileReader(const std::string& filename) {
  load_file(filename);
}

std::string ConfigFileReader::get(const std::string& name) {
  if (!loaded_) {
    return "";
  }

  auto it = config_map_.find(name);
  if (it == config_map_.end()) {
    return "";
  }

  return it->second;
}

int ConfigFileReader::set(const std::string& name, const std::string& value) {
  if (!loaded_) {
    return -1;
  }

  config_map_[name] = value;

  return write_file(config_file_);
}

void ConfigFileReader::load_file(const std::string& filename) {
  config_file_ = filename;
  std::string content = fileutils::read_whole_file(filename);
  std::string line;
  for (size_t i = 0; i < content.length(); ++i) {
    char c = content[i];
    if (c != '\n') {
      line.push_back(c);
      continue;
    }

    strutils::trim(line, " \r\n\t");

    // empty line
    if (line.length() == 0) {
      continue;
    }

    // comment
    if (line[0] == '#') {
      line.clear();
      continue;
    }

    // process line
    auto pos = line.find('=');
    if (pos == std::string::npos) {
      // invalid line
      continue;
    }

    std::string name = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    strutils::trim(name, " \r\n\t");
    strutils::trim(value, " \r\n\t");
    config_map_.insert(std::make_pair(name, value));
  }

  loaded_ = true;
}

int ConfigFileReader::write_file(const std::string& filename) {
  std::string content = to_string();
  return fileutils::write_to_file(filename, content);
}

std::string ConfigFileReader::to_string() {
  std::stringstream ss;
  for (const auto& pair : config_map_) {
    ss << pair.first << "=" << pair.second << "\n";
  }
  return ss.str();
}

}  // namespace mcppkits
