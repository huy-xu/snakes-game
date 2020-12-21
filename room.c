#include "room.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"

extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];
extern ListRoomPtr rooms;
int ID = 0;

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

void showRoom(int sessionID) {
  char temp[MAX];
  char response[MAX] = "success";
  ListRoomPtr currentRoomPtr = rooms;

  while (currentRoomPtr != NULL) {
    sprintf(temp, "-%d:%d", currentRoomPtr->room.id, numOfPlayers(currentRoomPtr->room.players));
    strcat(response, temp);
  }

  sendData(client_socket[sessionID], response);
}

void createRoom(int sessionID) {
  Room newRoom;
  char response[MAX];

  ID += 1;
  newRoom.id = ID;
  sprintf(newRoom.port, "%s%d", DEFAULT_PORT, ID);
  for (int i = 0; i < MAX_PLAYERS; i++) {
    strcpy(newRoom.players[i], "#");
  }

  strcpy(newRoom.players[0], sessions[sessionID].currentAccount.username);

  insertRoom(&rooms, newRoom);
  sessions[sessionID].room = newRoom;

  sprintf(response, "success-%d", newRoom.id);
  sendData(client_socket[sessionID], response);
}

void deleteRoom(ListRoomPtr sPtr, Room room) {
  ListRoomPtr tmp = sPtr;
  ListRoomPtr delRoom = malloc(sizeof(ListRoom));
  
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

int numOfPlayers(char players[MAX_PLAYERS][MAX]) {
  int total = 0;

  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (strcmp(players[i], "#") != 0) {
      total += 1;
    }
  }

  return total;
}

void joinRoom(int sessionID, char *body) {
  char response[MAX];
  int total;
  int roomID = atoi(body);
  ListRoomPtr currentRoom = findRoom(rooms, roomID);

  if (currentRoom == NULL) {
    strcpy(response, "error-Room not found");
    sendData(client_socket[sessionID], response);
  } else {
    if ((total = numOfPlayers(currentRoom->room.players)) == 4) {
      strcpy(response, "error-Room is full");
      sendData(client_socket[sessionID], response);
    } else {
      strcpy(currentRoom->room.players[total],
             sessions[sessionID].currentAccount.username);
      sessions[sessionID].room = currentRoom->room;

      strcpy(response, "success");

      for (int i = 0; i < MAX_PLAYERS; i++) {
        if (strcmp(currentRoom->room.players[i], "#") != 0) {
          strcat(response, "-");
          strcat(response, currentRoom->room.players[i]);
        }
      }

      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i].room.id == sessions[sessionID].room.id) {
          sendData(client_socket[i], response);
        }
      }
    }
  }
}

void sendChatMessage(int sessionID, char *body) {
  char response[MAX];

  sprintf(response, "%s: %s", sessions[sessionID].currentAccount.username, body);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == sessions[sessionID].room.id) {
      sendData(client_socket[i], response);
    }
  }
}

void startGame(int sessionID) {
  int socket;
  pthread_t thread_game;
  char startGame[MAX];
  char response[MAX];

  sprintf(startGame, "./startGame %s", sessions[sessionID].room.port);
  pthread_create(&thread_game, NULL, &handleStartGame, (void *)startGame);

  sprintf(response, "startGame-%s", sessions[sessionID].room.port);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == sessions[sessionID].room.id) {
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