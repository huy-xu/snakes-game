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
  SIGNIN,
  SIGNIN_SUCCESS,
  SIGNIN_FAIL,

  // Sign up
  SIGNUP,
  SIGNUP_SUCCESS,
  ACCOUNT_EXISTED,
  REPASS_NOT_MATCH,

  // Change password
  CHANGE_PASSWORD,
  CHANGE_PASSWORD_SUCCESS,
  CHANGE_PASSWORD_FAIL,

  // Sign out
  SIGNOUT,
  SIGNOUT_SUCCESS,

  // Show rank
  SHOW_RANK,
  SHOW_RANK_SUCCESS,

  // Show list room
  SHOW_ROOM,
  SHOW_ROOM_SUCCESS,

  // Create room
  CREATE_ROOM,
  CREATE_ROOM_SUCCESS,

  // Join room
  JOIN_ROOM,
  JOIN_ROOM_SUCCESS,
  ROOM_NOT_FOUND,
  ROOM_IS_FULL,

  // Chat
  CHAT,
  CHAT_SUCCESS,

  // Start game
  START_GAME,
  START_GAME_SUCCESS,

  // Leave room
  LEAVE_ROOM,
  LEAVE_ROOM_SUCCESS,
  PLAYER_LEFT_ROOM,

  // Quit game
  QUIT_GAME,

  // Sign in from other PC
  SIGNIN_OTHER_PC
} OPCODE;

#endif