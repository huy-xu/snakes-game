#include "account.h"

#include <stdio.h>
#include <string.h>

#include "constant.h"
#include "message.h"
#include "network.h"
#include "room.h"

extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];
extern ListAccountPtr accounts;

ListAccountPtr readData(char *fileName) {
  FILE *file;
  Account acc;
  ListAccountPtr sPtr = NULL;

  file = fopen(fileName, "r");

  while (!feof(file)) {
    fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
    insertAccount(&sPtr, acc);
  }

  fclose(file);

  return sPtr;
}

void writeData(char *fileName, ListAccountPtr sPtr) {
  FILE *file;
  Account acc;
  ListAccountPtr currentPtr = sPtr;

  file = fopen(fileName, "w");

  while (currentPtr != NULL) {
    acc = currentPtr->acc;
    fprintf(file, "%s %s %d\n", acc.username, acc.password, acc.scores);
    currentPtr = currentPtr->nextPtr;
  }

  fclose(file);
}

void insertAccount(ListAccountPtr *sPtr, Account acc) {
  ListAccountPtr newPtr, currentPtr, prevPtr;

  newPtr = malloc(sizeof(ListAccount));
  newPtr->acc = acc;
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

void printAccount(Account acc) {
  printf("%s %s %d\n", acc.username, acc.password, acc.scores);
}

void printListAccount(ListAccountPtr currentPtr) {
  while (currentPtr != NULL) {
    printAccount(currentPtr->acc);
    currentPtr = currentPtr->nextPtr;
  }
}

ListAccountPtr findAccount(ListAccountPtr sPtr, char *username) {
  if (sPtr == NULL) {
    return NULL;
  }
  if (strcmp(sPtr->acc.username, username) == 0) {
    return sPtr;
  } else {
    findAccount(sPtr->nextPtr, username);
  }
}

bool isValid(char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (!((str[i] >= '0' && str[i] <= '9') ||
          (str[i] >= 'A' && str[i] <= 'Z') ||
          (str[i] >= 'a' && str[i] <= 'z'))) {
      return false;
    }
  }

  return true;
}

bool isAuthenticated(char *username, char *password) {
  ListAccountPtr currentPtr = findAccount(accounts, username);

  if (currentPtr != NULL) {
    if (strcmp(currentPtr->acc.password, password) == 0) {
      return true;
    }
  }

  return false;
}

void signIn(int sessionID, char *data) {
  char *argv[2];
  char user[MAX], pass[MAX];
  Message *response = (Message *)malloc(sizeof(Message));

  splitData(argv, data);
  strcpy(user, argv[0]);
  strcpy(pass, argv[1]);
  if (!isAuthenticated(user, pass)) {
    response->code = SIGNIN_FAIL;
    strcpy(response->data, "Wrong username or password");
  } else {
    sessions[sessionID].currentAccount = findAccount(accounts, user)->acc;
    sessions[sessionID].room.id = -1;
    response->code = SIGNIN_SUCCESS;
    sprintf(response->data, "%s-%d",
            sessions[sessionID].currentAccount.username,
            sessions[sessionID].currentAccount.scores);
  }

  sendData(client_socket[sessionID], response);
}

void changePassword(int sessionID, char *data) {
  char *argv[2];
  char newPass[MAX], confirmPass[MAX];
  Message *response = (Message *)malloc(sizeof(Message));

  splitData(argv, data);
  strcpy(newPass, argv[0]);
  strcpy(confirmPass, argv[1]);

  if (strcmp(newPass, confirmPass) != 0) {
    response->code = CHANGE_PASSWORD_FAIL;
    strcpy(response->data, "Confirm password did not match");
  } else {
    ListAccountPtr current =
        findAccount(accounts, sessions[sessionID].currentAccount.username);
    strcpy(current->acc.password, newPass);
    writeData("src/account.txt", accounts);
    response->code = CHANGE_PASSWORD_SUCCESS;
    strcpy(response->data, "Change password successfully");
  }

  sendData(client_socket[sessionID], response);
}

void signUp(int sessionID, char *data) {
  Account acc;
  char *argv[3];
  char user[MAX], pass[MAX], confirmPass[MAX];
  Message *response = (Message *)malloc(sizeof(Message));

  splitData(argv, data);
  strcpy(user, argv[0]);
  strcpy(pass, argv[1]);
  strcpy(confirmPass, argv[2]);

  if (findAccount(accounts, user) != NULL) {
    response->code = ACCOUNT_EXISTED;
    strcpy(response->data, "Username has been existed");
  } else {
    if (strcmp(pass, confirmPass) != 0) {
      response->code = REPASS_NOT_MATCH;
      strcpy(response->data, "Confirm password did not matched");
    } else {
      strcpy(acc.username, user);
      strcpy(acc.password, pass);
      acc.scores = 0;
      insertAccount(&accounts, acc);
      writeData("src/account.txt", accounts);
      response->code = SIGNUP_SUCCESS;
      strcpy(response->data, "Sign up successfully");
    }
  }

  sendData(client_socket[sessionID], response);
}

void showRank(int sessionID) {
  Account arr[20];
  Message *response = (Message *)malloc(sizeof(Message));
  int count = 0;
  Account acc;
  Account tmp;
  int i, j;
  FILE *file;

  file = fopen("src/account.txt", "r");

  while (!feof(file)) {
    fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
    arr[count] = acc;
    count++;
  }

  for (i = 0; i < count; i++) {
    for (j = count - 1; j > i; j--) {
      if (arr[j].scores > arr[j - 1].scores) {
        tmp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = tmp;
      }
    }
  }

  char str[MAX];
  response->code = SHOW_RANK_SUCCESS;
  for (i = 0; i < 5; i++) {
    sprintf(str, "%s:%d-", arr[i].username, arr[i].scores);
    strcat(response->data, str);
  }

  ListAccountPtr current =
      findAccount(accounts, sessions[sessionID].currentAccount.username);
  for (i = 0; i < count; i++) {
    if (strcmp(arr[i].username, current->acc.username) == 0) {
      sprintf(str, "%s:%d", arr[i].username, arr[i].scores);
      strcat(response->data, str);
    }
  }

  fclose(file);

  sendData(client_socket[sessionID], response);
}

void signOut(int sessionID) {
  Message *response = (Message *)malloc(sizeof(Message));

  response->code = SIGNOUT_SUCCESS;
  strcpy(sessions[sessionID].currentAccount.username, "#");
  sessions[sessionID].currentAccount.scores = 0;
  sessions[sessionID].room.id = -1;
  sendData(client_socket[sessionID], response);
}