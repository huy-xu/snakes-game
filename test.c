#include <stdio.h>

#include "constant.h"
#include "message.h"

void main() {
  char res[MAX] = "chat-xu-abcxyz";
  Message message = handleResquest(res);

  printf("%s %ld\n", message.header);
  printf("%s %ld\n", message.body);

  return;
}