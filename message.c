#include "message.h"

#include <string.h>

Message handleRequest(char *request) {
  int i, j, k;
  Message message;
  char header[MAX], body[MAX];

  for (i = 0, j = 0, k = 0; i <= strlen(request); i++) {
    if (j >= 0) {
      if (request[i] != '-') {
        header[j] = request[i];
        j++;
      } else {
        header[j] = '\0';
        j = -1;
      }
    } else {
      body[k] = request[i];
      k++;
    }
  }
  if (j != -1) {
    header[j] = '\0';
  }
  body[k] = '\0';

  strcpy(message.header, header);
  strcpy(message.body, body);

  return message;
}
