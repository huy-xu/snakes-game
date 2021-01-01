#ifndef MESSAGE_H
#define MESSAGE_H

#include "constant.h"

typedef struct message {
  OPCODE code;   // opcode
  char data[MAX];  // save data field
} Message;
void setMessageResponse(Message *message);
Message handleRequest(char *request);
void splitBody(char **argv, char *body);

#endif