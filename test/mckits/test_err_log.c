#include "mckits_mlog.h"

int main() {
  err_ret("This is err_ret log: %d", 123);
  err_msg("This is err_msg log: %d", 456);
  err_dump("This will abort program: %d", 666);
  return 0;
}
