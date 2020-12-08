#include "constant.h"

typedef struct session {
  Account currentAccount;
  Room room;
} Session;

Session sessions[MAX_CLIENTS] = {{NULL, NULL}};