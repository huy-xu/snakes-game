#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "../server/message.h"
#include "constant.h"
#include "../server/constant.h"

int initClient(int port, char *ip);
int initServer(int port);
int acceptConnection(int sock);
int receiveData(int sock, Message *buff);
void sendData(int sock, char *buff);

#endif