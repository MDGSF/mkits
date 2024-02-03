#include "mckits/core/mckits_mlog.h"

int main() {
  mckits_global_loglevel = LOG_LEVEL_VERBOSE;
  verbolog("This is verbose log: %d", LOG_LEVEL_VERBOSE);
  dbglog("This is debug log: %d", LOG_LEVEL_DEBUG);
  infolog("This is info log: %d", LOG_LEVEL_INFO);
  warnlog("This is warn log: %d", LOG_LEVEL_WARNING);
  errlog("This is error log: %d", LOG_LEVEL_ERROR);
  fatallog("This is fatal log: %d", LOG_LEVEL_FATAL);
  return 0;
}
