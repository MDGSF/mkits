#ifndef MKITS_APPS_CALC24POINT_COMMON_MSG_H_
#define MKITS_APPS_CALC24POINT_COMMON_MSG_H_

#include <cstdint>

/*
@brief: deal cards
num1 num2 num3 num4\n
*/

enum class MsgType {
  MsgTypeWelcome = 1,
  MsgTypeInitCards = 2,
  MsgTypeChatMsg = 3,
};

struct MsgHeader {
  uint32_t package_size;
  uint32_t msg_type;
};

struct WelcomeMsg {
  MsgHeader header;
  char welcom_msg[32];
};

#endif  // MKITS_APPS_CALC24POINT_COMMON_MSG_H_
