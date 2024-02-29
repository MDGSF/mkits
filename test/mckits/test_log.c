#include "mckits/core/mckits_mlog.h"

int main() {
  mckits_global_loglevel = MKITS_LOG_LEVEL_VERBOSE;

  verbolog("This is verbose log");
  dbglog("This is debug log");
  infolog("This is info log");
  warnlog("This is warn log");
  errlog("This is error log");
  fatallog("This is fatal log\n");

  verbolog("This is verbose log: %d", MKITS_LOG_LEVEL_VERBOSE);
  dbglog("This is debug log: %d", MKITS_LOG_LEVEL_DEBUG);
  infolog("This is info log: %d", MKITS_LOG_LEVEL_INFO);
  warnlog("This is warn log: %d", MKITS_LOG_LEVEL_WARNING);
  errlog("This is error log: %d", MKITS_LOG_LEVEL_ERROR);
  fatallog("This is fatal log: %d", MKITS_LOG_LEVEL_FATAL);
  return 0;
}
