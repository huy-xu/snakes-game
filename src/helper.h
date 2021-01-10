#ifndef HELPER_H
#define HELPER_H

#include "constant.h"

typedef struct account {
  char username[MAX];
  char password[MAX];
  int scores;
} Account;

typedef struct listAccount {
  Account acc;
  struct listAccount *nextPtr;
} ListAccount;
typedef ListAccount *ListAccountPtr;

ListAccountPtr readData(char *fileName);
void writeScore(char *fileName, char *user);
void insertAccount(ListAccountPtr *sPtr, Account acc);
ListAccountPtr findAccount(ListAccountPtr sPtr, char *username);

#endif