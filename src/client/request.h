#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>

#include "constant.h"

typedef struct account {
  char username[MAX];
  int scores;
} Account;

void signIn(char *user, char *pass);
void changePassword();
void signUp();
void showRank();

#endif