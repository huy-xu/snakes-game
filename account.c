#include "account.h"

ListNodePtr readData(char *fileName) {
  FILE *file;
  Account acc;
  ListNodePtr sPtr = NULL;

  file = fopen(fileName, "r");

  while (!feof(file)) {
    fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
    insertLast(&sPtr, acc);
  }

  fclose(file);

  return sPtr;
}

void writeData(char *fileName, ListNodePtr sPtr) {
  FILE *file;
  Account acc;
  ListNodePtr currentPtr = sPtr;

  file = fopen(fileName, "w");

  while (currentPtr != NULL) {
    acc = currentPtr->acc;
    fprintf(file, "%s %s %d\n", acc.username, acc.password, acc.scores);
    currentPtr = currentPtr->nextPtr;
  }

  fclose(file);
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

// void blockAccount(char *username) {
//   ListNodePtr currentPtr = findNode(accounts, username);

//   if (currentPtr != NULL) {
//     currentPtr->acc.scores = 0;
//     writeData("account.txt", accounts);
//   }
// }

bool isAuthenticated(char *username, char *password) {
  ListNodePtr currentPtr = findNode(accounts, username);

  if (currentPtr != NULL) {
    if (strcmp(currentPtr->acc.password, password) == 0) {
      return true;
    }
  }

  return false;
}

char *signIn(Session *session, char *user, char *pass) {
  char result[20];
  if (strcmp((*session).currentUser, user) != 0) {
    strcpy((*session).currentUser, user);
  }
  if (!isAuthenticated(user, pass)) {
    return "error-input wrong";
  }
  (*session).currentAccount = findNode(accounts, user);
  strcpy(result,"success-");
  strcat(result,user);
  return result;
}

char *changePassword(Session *session, char *newPass) {

  strcpy((*session).currentAccount->acc.password, newPass);
  writeData("account.txt", accounts);

  return "success-Change pass success";
}

char *signOut(Session *session) {
  char *response = malloc(strlen("bye ") +
                          strlen((*session).currentAccount->acc.username) +
                          1);

  strcpy(response, "bye ");
  strcat(response, (*session).currentAccount->acc.username);
  (*session).currentAccount = NULL;
  strcpy((*session).currentUser, "#");

  return response;
}

void insertLast(ListNodePtr *sPtr, Account acc) {
  ListNodePtr newPtr, currentPtr, prevPtr;

  newPtr = malloc(sizeof(ListNode));
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

void printNode(Account acc) {
  printf("%s %s %d\n", acc.username, acc.password, acc.scores);
}

void printList(ListNodePtr currentPtr) {
  while (currentPtr != NULL) {
    printNode(currentPtr->acc);
    currentPtr = currentPtr->nextPtr;
  }
}

ListNodePtr findNode(ListNodePtr sPtr, char *username) {
  if (sPtr == NULL) {
    return NULL;
  }
  if (strcmp(sPtr->acc.username, username) == 0) {
    return sPtr;
  } else {
    findNode(sPtr->nextPtr, username);
  }
}
char *signUp(ListNodePtr *sPtr,char *user,char *pass, char *confirmPass){
  Account acc;
  char result[20];
  if (findNode(*sPtr,user)!=NULL){
    return "error-Account have been existed"
  }else{
    if(strcmp(pass,confirmPass)!=0){
      return "error-confirmPass wrong"
    }else{
      strcpy(acc.username,user);
      strcpy(acc.password,pass);
      acc.scores=0;
      insertLast(sPtr,acc);
      writeData("account.txt",*sPtr);
      strcpy(result,"success-");
      strcat(result,user);
    }
  }

  char *showRank(Account arr[20],int top){
    // output : listRank-top5-hiep:5-huy:5-tan:3
    char result[50];
    int count=0;
    Account acc;
    Account tmp;
    int i,j;
    FILE *file;
    file = fopen("account.txt","r");
    while (!feof(file)) {
    fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
    arr[count]=acc;
    count++;
    }
    for(i=0;i<count;i++){
      for(j=count-1;j>i;j--){
        if (arr[j].scores>arr[j-1].scores){
          tmp = arr[j];
          arr[j] = arr[j-1];
          arr[j-1] = tmp;
        }
      }
    }
    char str[5];
    strcpy(result,"listRank-top");
    strcat(result,sprintf(str,"%d",top));
    for(i=0;i<top;i++){
      strcat(result,sprintf(str,"-%s:%d",arr[i].username,arr[i].scores));
    }
    fclose(file);
  }

  return result;
}