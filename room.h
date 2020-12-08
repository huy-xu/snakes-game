#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "account.h"
#include "constant.h"

typedef struct room {
  int id;
  char port[MAX];
  char ip[MAX];
} Room;

typedef struct session {
  Account currentAccount;
  Room room;
} Session;

void joinRoom(int sessionID, char *body);
void sendChatMessage(Session session, char *body);

#endif