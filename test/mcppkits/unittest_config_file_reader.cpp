#include <cassert>
#include <iostream>

#include "mcppkits/mcppkits_config_file_reader.h"
#include "mcppkits/mcppkits_fileutils.h"
#include "mcppkits/mcppkits_random.h"

void test01() {
  std::string filename = mcppkits::random_tmp_filename(8, "mcppkits_test_");

  std::string content = R"(name = Mike
age = 18
sex = male
)";

  assert(0 == mcppkits::fileutils::write_to_file(filename, content));

  mcppkits::ConfigFileReader config(filename);

  assert("Mike" == config.get("name"));
  assert("18" == config.get("age"));
  assert("male" == config.get("sex"));
  assert("" == config.get("not_exists"));

  config.set("ip", "127.0.0.1");
  config.set("port", "12306");

  assert("127.0.0.1" == config.get("ip"));
  assert("12306" == config.get("port"));

  mcppkits::fileutils::remove_file(filename);
}

int main() {
  test01();
  return 0;
}
