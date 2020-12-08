// #include "account.h"

// ListNodePtr readData(char *fileName) {
//   FILE *file;
//   Account acc;
//   ListNodePtr sPtr = NULL;

//   file = fopen(fileName, "r");

//   while (!feof(file)) {
//     fscanf(file, "%s %s %d\n", acc.username, acc.password, &(acc.scores));
//     insertLast(&sPtr, acc);
//   }

//   fclose(file);

//   return sPtr;
// }

// void writeData(char *fileName, ListNodePtr sPtr) {
//   FILE *file;
//   Account acc;
//   ListNodePtr currentPtr = sPtr;

//   file = fopen(fileName, "w");

//   while (currentPtr != NULL) {
//     acc = currentPtr->acc;
//     fprintf(file, "%s %s %d\n", acc.username, acc.password, acc.scores);
//     currentPtr = currentPtr->nextPtr;
//   }

//   fclose(file);
// }

// bool isValid(char *str) {
//   for (int i = 0; i < strlen(str); i++) {
//     if (!((str[i] >= '0' && str[i] <= '9') ||
//           (str[i] >= 'A' && str[i] <= 'Z') ||
//           (str[i] >= 'a' && str[i] <= 'z'))) {
//       return false;
//     }
//   }

//   return true;
// }

// void blockAccount(char *username) {
//   ListNodePtr currentPtr = findNode(accounts, username);

//   if (currentPtr != NULL) {
//     currentPtr->acc.scores = 0;
//     writeData("account.txt", accounts);
//   }
// }

// bool isAuthenticated(char *username, char *password) {
//   ListNodePtr currentPtr = findNode(accounts, username);

//   if (currentPtr != NULL) {
//     if (strcmp(currentPtr->acc.password, password) == 0) {
//       return true;
//     }
//   }

//   return false;
// }

// char *signIn(Session *session, char *user, char *pass) {
//   if (strcmp((*session).currentUser, user) != 0) {
//     strcpy((*session).currentUser, user);
//     (*session).count = 0;
//   }
//   if (!isAuthenticated(user, pass)) {
//     (*session).count++;
//     if ((*session).count >= 3) {
//       blockAccount(user);
//       return "Account is blocked";
//     }
//     return "Not OK";
//   }
//   (*session).count = 0;
//   (*session).currentAccount = findNode(accounts, user);

//   if ((*session).currentAccount->acc.scores != 1) {
//     (*session).currentAccount = NULL;
//     strcpy((*session).currentUser, "#");
//     return "Account is not ready";
//   }

//   return "OK";
// }

// char *changePassword(Session *session, char *newPass) {
//   int i, j, k;
//   char *encodeNum = malloc(strlen(newPass) + 1);
//   char *encodeChar = malloc(strlen(newPass) + 1);

//   strcpy((*session).currentAccount->acc.password, newPass);
//   writeData("account.txt", accounts);

//   for (i = 0, j = 0, k = 0; i < strlen(newPass); i++) {
//     if (newPass[i] >= '0' && newPass[i] <= '9') {
//       encodeNum[j] = newPass[i];
//       j++;
//     } else {
//       encodeChar[k] = newPass[i];
//       k++;
//     }
//   }
//   encodeNum[j] = '\0';
//   encodeChar[k] = '\0';

//   strcat(encodeNum, encodeChar);

//   return encodeNum;
// }

// char *signOut(Session *session) {
//   char *response = malloc(strlen("Goodbye ") +
//                           strlen((*session).currentAccount->acc.username) +
//                           1);

//   strcpy(response, "Goodbye ");
//   strcat(response, (*session).currentAccount->acc.username);
//   (*session).currentAccount = NULL;
//   strcpy((*session).currentUser, "#");

//   return response;
// }

// void insertLast(ListNodePtr *sPtr, Account acc) {
//   ListNodePtr newPtr, currentPtr, prevPtr;

//   newPtr = malloc(sizeof(ListNode));
//   newPtr->acc = acc;
//   newPtr->nextPtr = NULL;

//   currentPtr = *sPtr;
//   prevPtr = NULL;

//   while (currentPtr != NULL) {
//     prevPtr = currentPtr;
//     currentPtr = currentPtr->nextPtr;
//   }

//   if (prevPtr == NULL) {
//     newPtr->nextPtr = *sPtr;
//     *sPtr = newPtr;
//   } else {
//     prevPtr->nextPtr = newPtr;
//     newPtr->nextPtr = currentPtr;
//   }
// }

// void printNode(Account acc) {
//   printf("%s %s %d\n", acc.username, acc.password, acc.scores);
// }

// void printList(ListNodePtr currentPtr) {
//   while (currentPtr != NULL) {
//     printNode(currentPtr->acc);
//     currentPtr = currentPtr->nextPtr;
//   }
// }

// ListNodePtr findNode(ListNodePtr sPtr, char *username) {
//   if (sPtr == NULL) {
//     return NULL;
//   }
//   if (strcmp(sPtr->acc.username, username) == 0) {
//     return sPtr;
//   } else {
//     findNode(sPtr->nextPtr, username);
//   }
// }