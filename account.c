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

void signIn(int sessionID, char *body) {
  char *argv[2];
  char user[MAX], pass[MAX];
  char response[MAX];

  splitBody(argv, body);
  strcpy(user, argv[0]);
  strcpy(pass, argv[1]);

  if (!isAuthenticated(user, pass)) {
    strcpy(response, "error-Wrong Username or Password");
  } else {
    sessions[sessionID].currentAccount = findAccount(accounts, user)->acc;
    sessions[sessionID].room.id = -1;
    sprintf(response, "success-%s-%d",
            sessions[sessionID].currentAccount.username,
            sessions[sessionID].currentAccount.scores);
  }

  sendData(client_socket[sessionID], response);
}

void changePassword(int sessionID, char *body) {
  char *argv[2];
  char newPass[MAX], confirmPass[MAX];
  char response[MAX];
  splitBody(argv,body);
  strcpy(newPass,argv[0]);
  strcpy(confirmPass,argv[1]);
  if(strcmp(newPass,confirmPass)!=0){
    strcpy(response,"error-Confirm password did not matched");
    sendData(client_socket[sessionID],response);
  } else{
    ListAccountPtr current = findAccount(accounts,sessions[sessionID].currentAccount.username);
    strcpy(current->acc.password,newPass);
    writeData("account.txt", accounts);
    strcpy(response,"success-Change password successfully");
    sendData(client_socket[sessionID],response);
  }
}

void signUp(int sessionID, char *body) {
  Account acc;
  char *argv[3];
  char user[MAX], pass[MAX], confirmPass[MAX];
  char response[MAX];

  splitBody(argv, body);
  strcpy(user, argv[0]);
  strcpy(pass, argv[1]);
  strcpy(confirmPass, argv[2]);

  if (findAccount(accounts, user) != NULL) {
    strcpy(response, "error-Username have been existed");
  } else {
    if (strcmp(pass, confirmPass) != 0) {
      strcpy(response, "error-Confirm password did not matched");
    } else {
      strcpy(acc.username, user);
      strcpy(acc.password, pass);
      acc.scores = 0;
      insertAccount(&accounts, acc);
      writeData("account.txt", accounts);
      strcpy(response, "success-Sign up successfully");
    }
  }

  sendData(client_socket[sessionID], response);
}

void showRank(int sessionID) {
    // output : listRank-top5-hiep:5-huy:5-tan:3
    Account arr[20];
    char response[MAX];
    int count = 0;
    Account acc;
    Account tmp;
    int i, j;
    FILE *file;
    file = fopen("account.txt", "r");
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
    char str[5];
    strcpy(response, "listRank");
    for (i = 0; i < 10; i++) {
      strcat(response, sprintf(str, "-%s:%d", arr[i].username,arr[i].scores));
    }
    ListAccountPtr current = findAccount(accounts,sessions[sessionID].currentAccount.username);
    for (i =0;i<count;i++){
      if (strcmp(arr[i].username, current->acc.username)==0){
        strcat(response,sprintf(str,"-%s:%d",arr[i].username,arr[i].scores));
      }
    }
    fclose(file);
    sendData(client_socket[sessionID],response);
  }