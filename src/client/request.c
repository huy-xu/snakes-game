#include <stdio.h>
#include <string.h>

#include "account.h"
#include "constant.h"
#include "network.h"

extern int sockfd;

void signIn(char *user, char *pass) {
  char request[MAX];

  sprintf(request, "signIn-%s-%s", user, pass);

  sendData(sockfd, request);
}