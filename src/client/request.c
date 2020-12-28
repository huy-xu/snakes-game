#include <stdio.h>
#include <string.h>

#include "account.h"
#include "constant.h"
#include "network.h"

extern int sockfd;

void signIn(char *user, char *pass) {
  char request[MAX];

  sprintf(request, "signIn-%s-%s", user, pass);

  sendData(sockfd, request);
}
void changePassword(char *newPass,char *reNewPass){
  char request[MAX];
  sprintf(request,"changePassword-%s-%s",newPass,reNewPass);
  sendData(sockfd,request);
}
void signUp(char *user, char *pass, char *confirmPass){
  char request[MAX];
  sprintf(request,"signUp-%s-%s-%s",user,pass,confirmPass);
  sendData(sockfd,request);
}
void showRank(){
  char request[MAX];
  sprintf(request,"showRank");
  sendData(sockfd,request);
}
void signOut(){
  char request[MAX];
  sprintf(request,"signOut");
  sendData(sockfd,request);
}
void createRoom(){
  char request[MAX];
  sprintf(request,"createRoom");
  sendData(sockfd,request);
}
void leaveRoom(){
  char request[MAX];
  sprintf(request,"leaveRoom");
  sendData(sockfd,request);
}
void showRoom(){
  char request[MAX];
  sprintf(request,"showRoom");
  sendData(sockfd,request);
}
void joinRoom(char *roomID){
  char request[MAX];
  sprintf(request,"joinRoom-%s",roomID);
  sendData(sockfd,request);
}
void chatRoom(char *message){
  char request[MAX];
  sprintf(request,"chat-%s",message);
  sendData(sockfd,request);
}
void startGame(){
  char request[MAX];
  sprintf(request,"startGame");
  sendData(sockfd,request);
}
