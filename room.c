#include "room.h"

#include <stdlib.h>

#include "network.h"

// Initialise all client_socket[] to 0 so not checked
extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];

char *listRoom(ListRoomPtr currentRoomPtr) {
  char list_room[MAX];
  while (currentRoomPtr != NULL) {
    strcat(list_room, itoa(currentRoomPtr->room.id));
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

void deleteRoom(ListRoomPtr *sPtr, Room room) {
  ListRoomPtr *tmp = sPtr;
  ListRoomPtr *delRoom = malloc(sizeof(ListRoom));
  int id;
  if (sPtr->room.id == room.id) {
    sPtr = sPtr->nextPtr;
    free(tmp);
  } else {
    while (tmp->next->room.id != room.id) {
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

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == session.room.id) {
      socket = client_socket[i];
      strcpy(response, session.currentAccount.username);
      strcat(response, ": ");
      strcat(response, body);
      sendData(socket, response);
    }
  }
}