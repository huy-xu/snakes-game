#include "account.h"

#include <stdio.h>
#include <string.h>

#include "constant.h"
#include "message.h"
#include "network.h"
#include "room.h"

extern int client_socket[MAX_CLIENTS];
extern Session sessions[MAX_CLIENTS];
ListAccountPtr accounts = NULL;

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
    strcpy(response, "error-Invalid Username or Password");
    sendData(client_socket[sessionID], response);
    return;
  }

  sessions[sessionID].currentAccount = findAccount(accounts, user)->acc;
  sessions[sessionID].room.id = -1;
  strcpy(response, "success-");
  strcat(response, user);

  sendData(client_socket[sessionID], response);
}

// char *changePassword(int sessionID, char *newPass) {
//   strcpy((*session).currentAccount->acc.password, newPass);
//   writeData("account.txt", accounts);

//   return "success-Change pass success";
// }

// void signOut(int sessionID) {
//   sessions[sessionID] = 
// }

// char *signUp(ListAccountPtr *sPtr, char *user, char *pass, char *confirmPass)
// {
//   Account acc;
//   char response[MAX];
//   if (findAccount(*sPtr, user) != NULL) {
//     return "error-Account have been existed"
//   } else {
//     if (strcmp(pass, confirmPass) != 0) {
//       return "error-confirmPass wrong"
//     } else {
//       strcpy(acc.username, user);
//       strcpy(acc.password, pass);
//       acc.scores = 0;
//       insertAccount(sPtr, acc);
//       writeData("account.txt", *sPtr);
//       strcpy(response, "success-");
//       strcat(response, user);
//     }
//   }

//   char *showRank(Account arr[20], int top) {
//     // output : listRank-top5-hiep:5-huy:5-tan:3
//     char response[50];
//     int count = 0;
//     Account acc;
//     Account tmp;
//     int i, j;
//     FILE *file;
//     file = fopen("account.txt", "r");
//     while (!feof(file)) {
//       fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
//       arr[count] = acc;
//       count++;
//     }
//     for (i = 0; i < count; i++) {
//       for (j = count - 1; j > i; j--) {
//         if (arr[j].scores > arr[j - 1].scores) {
//           tmp = arr[j];
//           arr[j] = arr[j - 1];
//           arr[j - 1] = tmp;
//         }
//       }
//     }
//     char str[5];
//     strcpy(response, "listRank-top");
//     strcat(response, sprintf(str, "%d", top));
//     for (i = 0; i < top; i++) {
//       strcat(response, sprintf(str, "-%s:%d", arr[i].username,
//       arr[i].scores));
//     }
//     fclose(file);
//   }

//   return response;
// }