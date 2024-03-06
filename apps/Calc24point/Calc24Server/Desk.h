#ifndef MKITS_APPS_CALC24POINT_CALC24SERVER_DESK_H_
#define MKITS_APPS_CALC24POINT_CALC24SERVER_DESK_H_

#define NO_PLAYER_ON_SEAET -1

struct Desk {
  int id;
  int clientfd1{NO_PLAYER_ON_SEAET};
  int clientfd2{NO_PLAYER_ON_SEAET};
  int clientfd3{NO_PLAYER_ON_SEAET};
};

#endif
