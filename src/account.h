#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h>

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
void writeData(char *fileName, ListAccountPtr sPtr);

void insertAccount(ListAccountPtr *sPtr, Account acc);
void printAccount(Account acc);
void printListAccount(ListAccountPtr currentPtr);
ListAccountPtr findAccount(ListAccountPtr sPtr, char *username);

bool isValid(char *str);
bool isAuthenticated(char *username, char *password);
void signIn(int sessionID, char *data);
void changePassword(int sessionID, char *data);
void signUp(int sessionID, char *data);
void showRank(int sessionID);
void signOut(int sessionID);

#endif