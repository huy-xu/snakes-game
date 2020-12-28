#ifndef MESSAGE_H
#define MESSAGE_H

#include "constant.h"

typedef struct message {
  char header[MAX];
  char body[MAX];
} Message;

Message handleRequest(char *request);
void splitBody(char **argv, char *body);

#endif