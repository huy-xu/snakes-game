#include "constant.h"

typedef struct room {
  int id;
  char port[MAX];
  char ip[MAX];
} Room;
typedef struct listRoom{
  Room room;
  struct listRoom *nextPtr;
} ListRoom;
typedef ListRoom *ListRoomPtr;

ListRoomPtr rooms = NULL;
void 
void joinRoom(Session *session, int roomID, char *buff);
void sendToOtherUsers(Session session, char *buff);
//update
char *listRoom(ListRoomPtr currentRoomPtr);
void insertRoom(ListRoomPtr *sPtr,Room room);
ListRoomPtr findRoom(ListRoomPtr sPtr,int id)
void deleteRoom(ListRoomPtr *sPtr,Room room);
//update
char *listRoom(ListRoomPtr currentRoomPtr){
  char list_room[MAX];
  while(currentRoomPtr!=NULL){
    strcat(list_room,itoa(currentRoomPtr->room.id));
    strcat(list_room,"-");
    currentRoomPtr=currentRoomPtr->nextPtr;
  }
  return list_room;
}

void insertRoom(ListRoomPtr *sPtr,Room room){
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
ListRoomPtr findRoom(ListRoomPtr sPtr,int id){
  if (sPtr == NULL) {
    return NULL;
  }
  if (sPtr->room.id == id) {
    return sPtr;
  } else {
    findRoom(sPtr->nextPtr, id);
  }
}
void deleteRoom(ListRoomPtr *sPtr,Room room){
  ListRoomPtr *tmp = sPtr;
  ListRoomPtr *delRoom = malloc(sizeof(ListRoom));
  int id;
  if(sPtr->room.id == room.id){
    sPtr = sPtr->nextPtr;
    free(tmp);
  }else{
    while(tmp->next->room.id != room.id){
      tmp = tmp->nextPtr;
    }
    delRoom = tmp->nextPtr;
    tmp->nextPtr = delRoom->nextPtr;
    delRoom->nextPtr = NULL;
    free(delRoom);
  }
}

void joinRoom(Session *session, int roomID, char *buff) {
  (*session).room.id = roomID;
}

void sendToOtherUsers(Session session, char *buff) {
  int socket;
  char message[MAX];

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (sessions[i].room.id == session.room.id) {
      socket = client_socket[i];
      strcpy(message, session.currentAccount.username);
      strcat(message, ": ");
      strcat(message, buff);
      sendData(socket, message);
    }
  }
}
