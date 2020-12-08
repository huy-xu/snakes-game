#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "list.h"
#include "account.h"
#include "constant.h"
#include "message.h"
#include "network.h"
#include "room.h"

// Initialise all client_socket[] to 0 so not checked
int client_socket[MAX_CLIENTS] = {0};
Session sessions[MAX_CLIENTS] = {{NULL, NULL}};

int main(int argc, char *argv[]) {
  int master_socket, new_socket, activity, addrlen, max_sd, sd, i;
  char request[BUFF_SIZE + 1];
  Message message;
  struct sockaddr_in address;
  fd_set readfds;

  if (argc != 2) {
    puts("Wrong parameter");
  } else {
    strcpy(sessions[0].currentAccount.username, "Xu");
    sessions[0].room.id = 1;

    strcpy(sessions[1].currentAccount.username, "Hiep");
    sessions[1].room.id = 1;

    strcpy(sessions[2].currentAccount.username, "Nam");
    sessions[2].room.id = 2;

    master_socket = initServer(atoi(argv[1]));

    // accounts = readData("account.txt");

    while (true) {
      // Clear the socket set
      FD_ZERO(&readfds);

      // Add master socket to set
      FD_SET(master_socket, &readfds);
      max_sd = master_socket;

      // Add child sockets to set
      for (i = 0; i < MAX_CLIENTS; i++) {
        // Socket descriptor
        sd = client_socket[i];

        // If valid socket descriptor then add to read list
        if (sd > 0) {
          FD_SET(sd, &readfds);
        }

        if (sd > max_sd) {
          max_sd = sd;
        }
      }

      // Wait for an activity on one of the sockets
      activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
      if (activity < 0) {
        perror("Select failed");
        exit(0);
      }

      // If something happened on the master socket ,
      // then its an incoming connection
      if (FD_ISSET(master_socket, &readfds)) {
        new_socket = acceptConnection(master_socket);
        for (i = 0; i < MAX_CLIENTS; i++) {
          if (client_socket[i] == 0) {
            client_socket[i] = new_socket;
            printf("Adding to list of sockets as %d\n", i);
            break;
          }
        }
      }

      // Else its some IO operation on some other socket
      for (i = 0; i < MAX_CLIENTS; i++) {
        sd = client_socket[i];

        if (FD_ISSET(sd, &readfds)) {
          // Check if it was for closing , and also read the
          // incoming message
          receiveData(sd, request);
          if (strcmp(request, "") == 0) {
            // Somebody disconnected, get details and print
            getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            printf("Host disconnected IP: %s, PORT: %d\n",
                   inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Close the socket and mark as 0 in list for reuse
            close(sd);
            client_socket[i] = 0;
          } else {
            message = handleResquest(request);
            if (strcmp(message.header, "joinRoom") == 0) {
              joinRoom(i, message.body);
            } else if (strcmp(message.header, "chat") == 0)
              sendChatMessage(sessions[i], message.body);
          }
        }
      }
    }
  }

  return 0;
}
