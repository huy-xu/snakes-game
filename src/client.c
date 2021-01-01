#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "message.h"
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
    //pthread_create(&thread_send, NULL, &send_message, NULL);
    //pthread_create(&thread_recv, NULL, &receive_message, NULL);
    Message *msg = (Message*) malloc(sizeof(Message));
    msg->code= LOGIN;
    strcpy(msg->data,"a-2");
    //send(sockfd,msg,sizeof(Message),0);
    printf("Hello %s",msg->data);
    close(sockfd);
  }

  return 0;
}

void *send_message() {
  Message *msg = (Message*) malloc(sizeof(Message));
  msg->code= LOGIN;
  strcpy(msg->data,"a-2");
  printf("%s",msg->data);
  send(sockfd,msg,sizeof(Message),0);
}

void *receive_message() {
  void *ptr;
  Message *message = (Message *) malloc(sizeof(Message));
  while (1) {
    recv(sockfd,ptr,sizeof(Message),0);
    message = (Message*)(ptr);
    printf("%s\n",message->data);
  }
}