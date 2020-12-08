#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdbool.h>

#include "constant.h"

typedef struct account {
  char username[MAX];
  char password[MAX];
  int scores;
} Account;

typedef struct listNode {
  Account acc;
  struct listNode *nextPtr;
} ListNode;
typedef ListNode *ListNodePtr;

// ListNodePtr accounts = NULL;

// ListNodePtr readData(char *fileName);
// void writeData(char *fileName, ListNodePtr sPtr);
// bool isValid(char *str);
// void blockAccount(char *username);
// bool isAuthenticated(char *username, char *password);
// char *signIn(Session *session, char *user, char *pass);
// char *changePassword(Session *session, char *newPass);
// char *signOut(Session *session);
// void insertLast(ListNodePtr *sPtr, Account acc);
// void printNode(Account acc);
// void printList(ListNodePtr currentPtr);
// ListNodePtr findNode(ListNodePtr sPtr, char *username);

#endif