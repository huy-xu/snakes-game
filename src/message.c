#include "message.h"

#include <string.h>
//set opcode
/*void setMessageResponse(Message *message){
  switch(message->code){
    case SIGNIN_SUCCESS:
      strcpy(message->mess,"SignIn Successfully ");
      break;
    case SIGNIN_FAIL:
      strcpy(message->mess,"SignIn Fail");
      break;
    case REGISTER_SUCCESS:
      strcpy(message->mess,"Register successfully");
      break;
    case ACCOUNT_EXISTED:
      strcpy(message->mess,"Account have been existed");
      break;
    case PASS_NOT_MATCH:
      strcpy(message->mess,"Password did not match");
      break;
    case CHANGE_PASSWORD_SUCCESS:
      strcpy(message->mess,"Change password successfully");
      break;
    case CHANGE_PASSWORD_FAIL:
      strcpy(message->mess,"Change password fail");
      break;
    case LOGOUT_SUCCESS:
      strcpy(message->mess,"Logout successfully");
      break;
    case SHOW_RANK_SUCCESS:
      strcpy(message->mess,"Show rank successfully");
      break;
    case CREATE_ROOM_SUCCESS:
      strcpy(message->mess,"Create room successfully");
      break;
    case JOIN_ROOM_SUCCESS:
      strcpy(message->mess,"Join room successfully");
      break;
    case JOIN_ROOM_FAIL:
      strcpy(message->mess,"Join room fail");
      break;
    case LEAVE_ROOM_SUCCESS:
      strcpy(message->mess,"Leave room successfully");
      break;
    case START_GAME_SUCCESS:
      strcpy(message->mess,"Start game successfully");
      break;
    case CHAT_SUCCESS:
      strcpy(message->mess,"Chat successfully");
      break;
  }
}*/
// Message handleRequest(char *request) {
//   int i, j, k;
//   Message *message = (Message*)malloc(sizeof(Message));
//   char header[MAX], data[MAX];

//   for (i = 0, j = 0, k = 0; i <= strlen(request); i++) {
//     if (j >= 0) {
//       if (request[i] != '-') {
//         header[j] = request[i];
//         j++;
//       } else {
//         header[j] = '\0';
//         j = -1;
//       }
//     } else {
//       data[k] = request[i];
//       k++;
//     }
//   }
//   if (j != -1) {
//     header[j] = '\0';
//   }
//   data[k] = '\0';
//   if (strcmp(header,"REGISTER")==0){
//     message->code = REGISTER;
//   } else if(strcmp(header,"LOGIN")){
//     message->code= LOGIN;
//   } else if(strcmp(header,"LOGOUT")){
//     message->code= LOGOUT;
//   } else if(strcmp(header,"CREATE_ROOM")){
//     message->code= CREATE_ROOM;
//   } else if(strcmp(header,"JOIN_ROOM")){
//     message->code= JOIN_ROOM;
//   } else if(strcmp(header,"LEAVE_ROOM")){
//     message->code= LEAVE_ROOM;
//   } else if(strcmp(header,"START_GAME")){
//     message->code= START_GAME;
//   } else if(strcmp(header,"SHOW_ROOM")){
//     message->code= SHOW_ROOM;
//   } else if(strcmp(header,"CHAT")){
//     message->code= CHAT;
//   } else if(strcmp(header,"CHANGE_PASSWORD")){
//     message->code= CHANGE_PASSWORD;
//   } else if(strcmp(header,"SHOW_RANK")){
//     message->code= SHOW_RANK;
//   } else if(strcmp(header,"SIGNIN_SUCCESS")){
//     message->code= SIGNIN_SUCCESS;
//   } else if(strcmp(header,"SIGNIN_FAIL")){
//     message->code= SIGNIN_FAIL;
//   } else if(strcmp(header,"REGISTER_SUCCESS")){
//     message->code= REGISTER_SUCCESS;
//   } else if(strcmp(header,"ACCOUNT_EXISTED")){
//     message->code= ACCOUNT_EXISTED;
//   } else if(strcmp(header,"PASS_NOT_MATCH")){
//     message->code= PASS_NOT_MATCH;
//   } else if(strcmp(header,"CHANGE_PASSWORD_SUCCESS")){
//     message->code= CHANGE_PASSWORD_SUCCESS;
//   } else if(strcmp(header,"CHANGE_PASSWORD_FAIL")){
//     message->code= CHANGE_PASSWORD_FAIL;
//   } else if(strcmp(header,"LOGOUT_SUCCESS")){
//     message->code= LOGOUT_SUCCESS;
//   } else if(strcmp(header,"SHOW_RANK_SUCCESS")){
//     message->code= SHOW_RANK_SUCCESS;
//   } else if(strcmp(header,"CREATE_ROOM_SUCCESS")){
//     message->code= CREATE_ROOM_SUCCESS;
//   } else if(strcmp(header,"JOIN_ROOM_SUCCESS")){
//     message->code= JOIN_ROOM_SUCCESS;
//   } else if(strcmp(header,"JOIN_ROOM_FAIL")){
//     message->code= JOIN_ROOM_FAIL;
//   } else if(strcmp(header,"LEAVE_ROOM_SUCCESS")){
//     message->code= LEAVE_ROOM_SUCCESS;
//   } else if(strcmp(header,"START_GAME_SUCCESS")){
//     message->code= START_GAME_SUCCESS;
//   } else if(strcmp(header,"SHOW_ROOM_SUCCESS")){
//     message->code= SHOW_ROOM_SUCCESS;
//   } else if(strcmp(header,"CHAT_SUCCESS")){
//     message->code= CHAT_SUCCESS;
//   }
//   strcpy(message->data, data);

//   return message;
// }

void splitBody(char **argv, char *body) {
  int i = 0;
  char *token = strtok(body, "-");

  while (token != NULL) {
    argv[i++] = token;
    token = strtok(NULL, "-");
  }
}