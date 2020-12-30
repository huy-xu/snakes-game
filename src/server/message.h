#ifndef MESSAGE_H
#define MESSAGE_H

#include "constant.h"

typedef struct message {
  OPCODE code;   // opcode
  char mess[MAX];  // message
  char body[MAX];  // save data field
} Message;
void setMessageResponse(Message *message);
Message handleRequest(char *request);
void splitBody(char **argv, char *body);

#endif