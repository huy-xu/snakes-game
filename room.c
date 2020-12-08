#include "room.h"

#include <stdlib.h>
#include "network.h"

// Initialise all client_socket[] to 0 so not checked
extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];

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