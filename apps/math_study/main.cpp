#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "mckits/core/mckits_mrandom.h"

std::string gen_one_line(int questions_per_line) {
  std::stringstream liness;
  for (int i = 0; i < questions_per_line; ++i) {
    if (i != 0) {
      liness << "    ";
    }

    int n1 = mckits_random_num(0, 11);
    int n2 = mckits_random_num(0, 11);
    int op = mckits_random_num(0, 2);
    if (op == 0) {
      liness << std::right << std::setw(3) << std::setfill(' ') << n1 << " + "
             << std::left << std::setw(2) << std::setfill(' ') << n2 << " =   ";
    } else {
      if (n1 >= n2) {
        liness << std::right << std::setw(3) << std::setfill(' ') << n1 << " - "
               << std::left << std::setw(2) << std::setfill(' ') << n2
               << " =   ";
      } else {
        liness << std::right << std::setw(3) << std::setfill(' ') << n2 << " - "
               << std::left << std::setw(2) << std::setfill(' ') << n1
               << " =   ";
      }
    }
  }
  liness << std::endl;
  return liness.str();
}

int main() {
  int questions_num = 100;
  int questions_per_line = 3;
  int line_num = questions_num / questions_per_line;

  std::stringstream result;
  for (int i = 0; i < line_num; ++i) {
    std::string line = gen_one_line(questions_per_line);
    result << line;
  }
  std::cout << result.str() << std::endl;

  return 0;
}
