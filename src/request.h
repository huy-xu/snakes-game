#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>

#include "constant.h"

typedef struct account {
  char username[MAX];
  int scores;
} Account;

void signIn(char *user, char *pass);
void changePassword(char *newPass,char *reNewPass);
void signUp(char *user, char *pass, char *confirmPass);
void showRank();
void signOut();
void createRoom();
void leaveRoom();
void showRoom();
void joinRoom(char *roomID);
void chatRoom(char *message);
void startGame();
#endif