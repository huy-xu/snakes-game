#ifndef CONSTANT_H
#define CONSTANT_H

#define MAX 100
#define BUFF_SIZE 1024
#define MAX_CLIENTS 5
#define MAX_ROOMS 5
#define MAX_PLAYERS 4
#define SERVER_IP "192.168.43.23"
#define DEFAULT_PORT "900"
typedef enum OPCODE{
    REGISTER,
    LOGIN,              
    LOGOUT,
    CREATE_ROOM,                                
    JOIN_ROOM,               
    LEAVE_ROOM,           
    START_GAME,
    SHOW_ROOM,
    CHAT,
    CHANGE_PASSWORD,
    SHOW_RANK,
    SIGNIN_SUCCESS,
    SIGNIN_FAIL,
    REGISTER_SUCCESS,
    ACCOUNT_EXISTED,
    PASS_NOT_MATCH,
    CHANGE_PASSWORD_SUCCESS,
    CHANGE_PASSWORD_FAIL,
    LOGOUT_SUCCESS,
    SHOW_RANK_SUCCESS,
    CREATE_ROOM_SUCCESS,
    JOIN_ROOM_SUCCESS,
    JOIN_ROOM_FAIL,
    LEAVE_ROOM_SUCCESS,
    START_GAME_SUCCESS,
    SHOW_ROOM_SUCCESS,
    CHAT_SUCCESS
}OPCODE;

#endif