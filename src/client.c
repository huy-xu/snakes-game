#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "gui.h"
#include "network.h"
#include "request.h"

void quitGameHandler(int tmp);

int sockfd;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    puts("Wrong parameter");
  } else {
    sockfd = initClient(atoi(argv[2]), argv[1]);
    signal(SIGINT, quitGameHandler);
    gui(sockfd);
    close(sockfd);
  }

  return 0;
}

void quitGameHandler(int tmp) {
  quitGameReq(sockfd);
  exit(0);
}