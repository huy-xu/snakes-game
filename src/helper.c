#include "helper.h"

#include <stdio.h>
#include <string.h>

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

void writeScore(char *fileName, char *user) {
  FILE *file;
  Account acc;
  ListAccountPtr sPtr = readData(fileName);
  ListAccountPtr currentPtr = findAccount(sPtr, user);

  currentPtr->acc.scores++;

  file = fopen(fileName, "w");

  while (sPtr != NULL) {
    acc = sPtr->acc;
    fprintf(file, "%s %s %d\n", acc.username, acc.password, acc.scores);
    sPtr = sPtr->nextPtr;
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