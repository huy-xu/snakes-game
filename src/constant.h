#ifndef CONSTANT_H
#define CONSTANT_H

#define MAX 100
#define BUFF_SIZE 1024
#define MAX_CLIENTS 5
#define MAX_ROOMS 5
#define MAX_PLAYERS 4
#define SERVER_IP "192.168.43.23"
#define DEFAULT_PORT "900"
typedef enum OPCODE {
  // Sign in
  SIGNIN,          // 0
  SIGNIN_SUCCESS,  // 1
  SIGNIN_FAIL,     // 2

  // Sign up
  SIGNUP,            // 3
  SIGNUP_SUCCESS,    // 4
  ACCOUNT_EXISTED,   // 5
  REPASS_NOT_MATCH,  // 6

  // Change password
  CHANGE_PASSWORD,          // 7
  CHANGE_PASSWORD_SUCCESS,  // 8
  CHANGE_PASSWORD_FAIL,     // 9

  // Sign out
  SIGNOUT,          // 10
  SIGNOUT_SUCCESS,  // 11

  // Show rank
  SHOW_RANK,          // 12
  SHOW_RANK_SUCCESS,  // 13

  // Show list room
  SHOW_ROOM,          // 14
  SHOW_ROOM_SUCCESS,  // 15

  // Create room
  CREATE_ROOM,          // 16
  CREATE_ROOM_SUCCESS,  // 17

  // Join room
  JOIN_ROOM,          // 18
  JOIN_ROOM_SUCCESS,  // 19
  ROOM_NOT_FOUND,     // 20
  ROOM_IS_FULL,       // 21

  // Chat
  CHAT,          // 22
  CHAT_SUCCESS,  // 23

  // Start game
  START_GAME,          // 24
  START_GAME_SUCCESS,  // 25

  // Leave room
  LEAVE_ROOM,          // 26
  LEAVE_ROOM_SUCCESS,  // 27
  PLAYER_LEFT_ROOM,    // 28

  // Quit game
  QUIT_GAME,  // 29

  // Sign in from other PC
  SIGNIN_OTHER_PC  // 30
} OPCODE;

#endif