#include "room.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "network.h"
extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];
extern ListRoomPtr rooms;
int ID = 0;

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
  ListRoomPtr tempPtr, currentPtr, prevPtr;

  tempPtr = NULL;
  prevPtr = NULL;
  currentPtr = *sPtr;

  if ((*sPtr)->room.id == room.id) {
    tempPtr = *sPtr;
    *sPtr = (*sPtr)->nextPtr;
    free(tempPtr);
  } else {
    while (currentPtr != NULL && room.id != currentPtr->room.id) {
      prevPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
      tempPtr = currentPtr;
      prevPtr->nextPtr = currentPtr->nextPtr;
      currentPtr = currentPtr->nextPtr;
      free(tempPtr);
    }
  }
}

void showRoom(int sessionID) {
  char temp[MAX];
  Message *response = (Message *)malloc(sizeof(Message));
  ListRoomPtr currentRoomPtr = rooms;
  response->code = SHOW_ROOM_SUCCESS;

  while (currentRoomPtr != NULL) {
    sprintf(temp, "%d-%d", currentRoomPtr->room.id,
            numOfPlayers(currentRoomPtr->room.players));
    strcat(response->data, temp);
    currentRoomPtr = currentRoomPtr->nextPtr;
  }

  sendData(client_socket[sessionID], response);
}

void createRoom(int sessionID) {
  Room newRoom;
  Message *response = (Message *)malloc(sizeof(Message));

  ID += 1;
  newRoom.id = ID;
  sprintf(newRoom.port, "%s%d", DEFAULT_PORT, ID);
  for (int i = 0; i < MAX_PLAYERS; i++) {
    strcpy(newRoom.players[i], "#");
  }

  strcpy(newRoom.players[0], sessions[sessionID].currentAccount.username);

  insertRoom(&rooms, newRoom);
  sessions[sessionID].room = newRoom;
  response->code = CREATE_ROOM_SUCCESS;

  sprintf(response->data, "%d", newRoom.id);

  sendData(client_socket[sessionID], response);
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

void joinRoom(int sessionID, char *data) {
  Message *response = (Message *)malloc(sizeof(Message));
  int total;
  int roomID = atoi(data);
  ListRoomPtr currentRoom = findRoom(rooms, roomID);

  if (currentRoom == NULL) {
    response->code = ROOM_NOT_FOUND;

    sendData(client_socket[sessionID], response);
  } else {
    if ((total = numOfPlayers(currentRoom->room.players)) == 4) {
      response->code = ROOM_IS_FULL;

      sendData(client_socket[sessionID], response);
    } else {
      for (int i = 0; i < MAX_PLAYERS; i++) {
        if (strcmp(currentRoom->room.players[i], "#") != 0) {
          strcat(response->data, currentRoom->room.players[i]);
          strcat(response->data, "-");
        }
      }
      strcat(response->data, sessions[sessionID].currentAccount.username);

      response->code = JOIN_ROOM_SUCCESS;
      strcpy(currentRoom->room.players[total],
             sessions[sessionID].currentAccount.username);
      sessions[sessionID].room = currentRoom->room;

      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (sessions[i].room.id == sessions[sessionID].room.id) {
          sendData(client_socket[i], response);
        }
      }
    }
  }
}

void leaveRoom(int sessionID) {
  Message *response = (Message *)malloc(sizeof(Message));
  int roomID = sessions[sessionID].room.id;
  ListRoomPtr currentRoomPtr = findRoom(rooms, sessions[sessionID].room.id);

  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (strcmp(currentRoomPtr->room.players[i],
               sessions[sessionID].currentAccount.username) == 0) {
      strcpy(currentRoomPtr->room.players[i], "#");
      break;
    }
  }
  sessions[sessionID].room.id = -1;

  response->code = LEAVE_ROOM_SUCCESS;
  sprintf(response->data, "%s", sessions[sessionID].currentAccount.username);

  if (numOfPlayers(currentRoomPtr->room.players) == 0) {
    deleteRoom(&rooms, currentRoomPtr->room);
  }

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == roomID) {
      sendData(client_socket[i], response);
    }
  }

  sendData(client_socket[sessionID], response);
}

void sendChatMessage(int sessionID, char *data) {
  Message *response = (Message *)malloc(sizeof(Message));
  response->code = CHAT_SUCCESS;

  sprintf(response->data, "%s: %s", sessions[sessionID].currentAccount.username,
          data);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == sessions[sessionID].room.id) {
      sendData(client_socket[i], response);
    }
  }
}

void startGame(int sessionID) {
  pthread_t thread_game;
  char startGame[MAX];
  Message *response = (Message *)malloc(sizeof(Message));

  sprintf(startGame, "./startGame %s", sessions[sessionID].room.port);
  pthread_create(&thread_game, NULL, &handleStartGame, (void *)startGame);
  response->code = START_GAME_SUCCESS;

  sprintf(response->data, "startGame-%s", sessions[sessionID].room.port);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == sessions[sessionID].room.id) {
      sendData(client_socket[i], response);
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