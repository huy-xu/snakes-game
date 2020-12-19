#include "room.h"

#include <pthread.h>
#include <stdlib.h>

#include "network.h"

extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];

char *listRoom(ListRoomPtr currentRoomPtr) {
  char list_room[MAX];
  char str[MAX];
  while (currentRoomPtr != NULL) {
    strcat(list_room, sprintf(str, "%d", currentRoomPtr->room.id));
    strcat(list_room, "-");
    currentRoomPtr = currentRoomPtr->nextPtr;
  }
  return list_room;
}

void insertRoom(ListRoomPtr *sPtr, Room room) {
  ListRoomPtr newPtr, currentPtr, prevPtr;

  newPtr = malloc(sizeof(ListRoom));
  newPtr->room = room;
  newPtr->nextPtr = NULL;

  currentPtr = *sPtr;
  prevPtr = NULL;

  while (currentPtr != NULL) {
    prevPtr = currentPtr;
    currentPtr = currentPtr->nextPtr;
  }

  if (prevPtr == NULL) {
    newPtr->nextPtr = *sPtr;
    *sPtr = newPtr;
  } else {
    prevPtr->nextPtr = newPtr;
    newPtr->nextPtr = currentPtr;
  }
}

ListRoomPtr findRoom(ListRoomPtr sPtr, int id) {
  if (sPtr == NULL) {
    return NULL;
  }
  if (sPtr->room.id == id) {
    return sPtr;
  } else {
    findRoom(sPtr->nextPtr, id);
  }
}

void deleteRoom(ListRoomPtr sPtr, Room room) {
  ListRoomPtr tmp = sPtr;
  ListRoomPtr delRoom = malloc(sizeof(ListRoom));
  int id;
  if (tmp->room.id == room.id) {
    sPtr = sPtr->nextPtr;
    free(tmp);
  } else {
    while (tmp->nextPtr->room.id != room.id) {
      tmp = tmp->nextPtr;
    }
    delRoom = tmp->nextPtr;
    tmp->nextPtr = delRoom->nextPtr;
    delRoom->nextPtr = NULL;
    free(delRoom);
  }
}

void joinRoom(int sessionID, char *body) {
  char response[MAX] = "Joined Room ";
  int roomID = atoi(body);

  sessions[sessionID].room.id = roomID;
  strcat(response, body);

  sendData(client_socket[sessionID], response);
}

void sendChatMessage(Session session, char *body) {
  int socket;
  char response[MAX];

  strcpy(response, session.currentAccount.username);
  strcat(response, ": ");
  strcat(response, body);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == session.room.id) {
      socket = client_socket[i];
      sendData(socket, response);
    }
  }
}

void startGame(Session session) {
  int socket;
  pthread_t thread_game;
  char startGame[MAX] = "./startGame ";
  char response[MAX] = "success-";

  strcat(startGame, session.room.port);

  pthread_create(&thread_game, NULL, &handleStartGame, (void *)startGame);

  strcat(response, session.room.ip);
  strcat(response, "-");
  strcat(response, session.room.port);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == session.room.id) {
      socket = client_socket[i];
      sendData(socket, response);
    }
  }
}

void *handleStartGame(void *arg) {
  pthread_detach(pthread_self());
  char startGame[MAX];

  strcpy(startGame, (char *)arg);
  printf("%s\n", startGame);

  system(startGame);
}