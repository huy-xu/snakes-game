#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include "account.h"
#include "constant.h"

typedef struct room {
  int id;
  char port[MAX];
  char ip[MAX];
  char players[MAX_PLAYERS][MAX];
} Room;

typedef struct listRoom {
  Room room;
  struct listRoom *nextPtr;
} ListRoom;
typedef ListRoom *ListRoomPtr;

typedef struct session {
  Account currentAccount;
  Room room;
} Session;

char *listRoom(ListRoomPtr currentRoomPtr);
void insertRoom(ListRoomPtr *sPtr, Room room);
ListRoomPtr findRoom(ListRoomPtr sPtr, int id);
void deleteRoom(ListRoomPtr sPtr, Room room);

void showRoom(int sessionID);
void createRoom(int sessionID);
int numOfPlayers(char players[MAX_PLAYERS][MAX]);
void joinRoom(int sessionID, char *body);
void exitRoom(int sessionID);
void sendChatMessage(Session session, char *body);
void startGame(Session session);
void *handleStartGame(void *arg);

#endif
