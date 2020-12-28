#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "request.h"

void *send_message();
void *receive_message();

int sockfd;
char buff[BUFF_SIZE + 1] = "#";

int main(int argc, char *argv[]) {
  pthread_t thread_send, thread_recv;

  if (argc != 3) {
    puts("Wrong parameter");
  } else {
    sockfd = initClient(atoi(argv[2]), argv[1]);

    // Communicate with server
    pthread_create(&thread_send, NULL, &send_message, NULL);
    pthread_create(&thread_recv, NULL, &receive_message, NULL);

    while (strlen(buff) != 0)
      ;
    close(sockfd);
  }

  return 0;
}

void *send_message() {
  while (1) {
    gets(buff);
    if (strlen(buff) == 0) {
      break;
    }

    sendData(sockfd, buff);
  }
}

void *receive_message() {
  while (1) {
    receiveData(sockfd, buff);
    printf("%s\n", buff);
  }
}