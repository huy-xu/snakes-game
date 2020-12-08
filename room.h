#include "constant.h"

typedef struct room {
  int id;
  char port[MAX];
  char ip[MAX];
} Room;

void joinRoom(Session *session, int roomID, char *buff);
void sendToOtherUsers(Session session, char *buff);

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