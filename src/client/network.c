#include "network.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int initClient(int port, char *ip) {
  int sock, count = 0;
  struct sockaddr_in server;

  // Check valid port
  if (port == 0) {
    puts("Invalid port number");
    exit(0);
  }

  // Check valid IP
  for (int i = 0; i < strlen(ip); i++) {
    if (ip[i] == '.') {
      count++;
    }
  }
  if (inet_addr(ip) == -1 || count != 3) {
    puts("Invalid IP address");
    exit(0);
  }

  // Creating socket file descriptor
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket failed");
    exit(0);
  }

  // Filling server information
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ip);
  bzero(&(server.sin_zero), sizeof(server));

  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Connection failed");
    exit(0);
  }

  return sock;
}

int initServer(int port) {
  int sock, opt = true;
  struct sockaddr_in server;

  if (port == 0) {
    perror("Invalid port number");
    exit(0);
  }

  // Creating socket file descriptor
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket failed");
    exit(0);
  }

  // set master socket to allow multiple connections ,
  // this is just a good habit, it will work without this
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) <
      0) {
    perror("Set sockopt failed");
    exit(0);
  }

  // Filling server information
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  bzero(&(server.sin_zero), sizeof(server));

  // Bind address to socket
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("Bind failed");
    exit(0);
  }

  // Try to specify maximum of 5 pending connections for the master socket
  if (listen(sock, 5) < 0) {
    perror("Listen failed");
    exit(0);
  }

  printf("Server started at %s\n", inet_ntoa(server.sin_addr));

  return sock;
}

int acceptConnection(int sock) {
  int new_socket, len;
  struct sockaddr_in client;

  len = sizeof(client);
  new_socket = accept(sock, (struct sockaddr *)&client, &len);
  if (new_socket < 0) {
    perror("Accept failed");
    exit(0);
  }
  printf("Connection accepted from %s: %d\n", inet_ntoa(client.sin_addr),
         ntohs(client.sin_port));

  return new_socket;
}

int receiveData(int sock, Message *buff) {
  int recvBytes;

  recvBytes = recv(sock, buff,sizeof(Message), 0);
  if (recvBytes < 0) {
    perror("Recv failed");
    exit(0);
  }
  return recvBytes;
}

void sendData(int sock, char *buff) {
  if (send(sock, buff, BUFF_SIZE-1, 0) < 0) {
    perror("Send failed");
    exit(0);
  }
}