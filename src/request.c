#include <stdio.h>
#include <string.h>

#include "account.h"
#include "constant.h"
#include "message.h"
#include "network.h"

extern int sockfd;
void signInReq(int serverfd, char *user, char *pass) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = SIGNIN;
  sprintf(request->data, "%s-%s", user, pass);
  sendData(serverfd, request);
}

// TODO
void changePasswordReq(int serverfd, char *newPass, char *reNewPass) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = CHANGE_PASSWORD;
  sprintf(request->data, "%s-%s", newPass, reNewPass);
  sendData(serverfd, request);
}

void signUpReq(int serverfd, char *user, char *pass, char *confirmPass) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = SIGNUP;
  sprintf(request->data, "%s-%s-%s", user, pass, confirmPass);
  sendData(serverfd, request);
}

void showRankReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = SHOW_RANK;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}

void signOutReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = SIGNOUT;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}

void createRoomReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = CREATE_ROOM;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}

void leaveRoomReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = LEAVE_ROOM;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}

void showRoomReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = SHOW_ROOM;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}

void joinRoomReq(int serverfd, char *roomID) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = JOIN_ROOM;
  strcpy(request->data, roomID);
  sendData(serverfd, request);
}

void chatRoomReq(int serverfd, char *message) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = CHAT;
  strcpy(request->data, message);
  sendData(serverfd, request);
}

void startGameReq(int serverfd) {
  Message *request = (Message *)malloc(sizeof(Message));

  request->code = START_GAME;
  strcpy(request->data, "#");
  sendData(serverfd, request);
}