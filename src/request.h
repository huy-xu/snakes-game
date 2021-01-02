#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>

#include "constant.h"

typedef struct account {
  char username[MAX];
  int scores;
} Account;

void signInReq(int serverfd, char *user, char *pass);

//TODO
void changePasswordReq(int serverfd, char *newPass, char *reNewPass);
void signUpReq(int serverfd, char *user, char *pass, char *confirmPass);
void showRankReq(int serverfd);
void signOutReq(int serverfd);
void createRoomReq(int serverfd);
void leaveRoomReq(int serverfd);
void showRoomReq(int serverfd);
void joinRoomReq(int serverfd, char *roomID);
void chatRoomReq(int serverfd, char *message);
void startGameReq(int serverfd);

#endif