#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "constant.h"
#include "message.h"
int initClient(int port, char *ip);
int initServer(int port);
int acceptConnection(int sock);
int receiveData(int sock, char *buff);
void sendData(int sock, Message *buff);

#endif