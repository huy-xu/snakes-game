#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#include "constant.h"
#include "message.h"

#define GLADE_FILE_NAME "glade/clientGUI.glade"
#define GLADE_CSS "glade/style.css"

// ID Window
#define WINDOW_MAIN "window_main"
#define WINDOW_ALERT "window_alert"

// ID Stack
// #define STACK_CONTAINER "stack_container"
// #define STACK_MENU "stack_menu"
#define STACK_HOME "stack_home"
#define STACK_MENU "stack_menu"
#define STACK_ALERT "stack_alert"

// ID Container
#define CONTAINER_MENU "container_menu"
#define CONTAINER_FEATURE "container_feature"
#define CONTAINER_LISTROOM "container_listroom"
#define CONTAINER_CHANGEPAS "container_changepas"
#define CONTAINER_MENU_LOG "container_menu_log"
#define CONTAINER_MENU_REG "container_menu_reg"
#define CONTAINER_ROOMVIEW "container_roomview"
#define CONTAINER_SHOWRANK "container_rank"
#define NUMBER_OF_CONTAINER 6
#define ALERT_ROOM_NOT_FOUND "alert_room_not_found"

// ID Entry
#define ENTRY_MENU_LOG_USER "entry_menu_log_user"
#define ENTRY_MENU_LOG_PAS "entry_menu_log_pas"
#define ENTRY_CHANGEPAS_NEW "entry_changepas_new"
#define ENTRY_CHANGEPAS_CONFIRM "entry_changepas_confirm"
#define ENTRY_CHAT "entry_chat"

// ID Clickable Button
#define BTN_MENU_REG "btn_menu_log_reg"
#define BTN_LISTROOM_CREATE_ROOM "btn_create_room"
#define BTN_JOIN_GAME "btn_join_game"
#define BTN_LEAVE_ROOM "btn_leave_room"
#define BTN_SEND_MESS "btn_send_mess"
#define BTN_LOGOUT "btn_logout"
#define BTN_REFRESH "btn_refresh"

// ID label
#define LBL_USER_NAME "lbl_user_name"
#define LBL_SCORE "lbl_score"
#define LBL_PLAYER_1 "player_name_1"
#define LBL_PLAYER_2 "player_name_2"
#define LBL_PLAYER_3 "player_name_3"
#define LBL_PLAYER_4 "player_name_4"
#define LBL_ERROR "lbl_error"
#define LBL_YOUR_SCORE "lbl_your_score"
#define LBL_YUOR_RANK "lbl_your_rank"
#define LBL_RANK_USER1 "lbl_rank_user1"
#define LBL_RANK_USER2 "lbl_rank_user2"
#define LBL_RANK_USER3 "lbl_rank_user3"
#define LBL_RANK_USER4 "lbl_rank_user4"
#define LBL_RANK_USER5 "lbl_rank_user5"
#define LBL_SCORE1 "lbl_score1"
#define LBL_SCORE2 "lbl_score2"
#define LBL_SCORE3 "lbl_score3"
#define LBL_SCORE4 "lbl_score4"
#define LBL_SCORE5 "lbl_score5"

// Text view
#define TXT_CHAT_VIEW "txt_chat_view"

typedef struct {
  int currentWindow;
  int serverfd;
  Message *msg;

  GtkEntry  *w_entry_menu_log_user, 
            *w_entry_menu_log_pas,
            *w_entry_changepas_new,
            *w_entry_changepas_confirm,
            *w_entry_chat;
  GtkStack  *w_stack_home, *w_stack_menu, *a_stack_alert;
  GtkWidget *w_container_feature, 
            *w_container_listroom, 
            *w_container_menu, 
            *w_container_menu_reg, 
            *w_container_menu_log, 
            *w_container_changepas,
            *w_roomView,
            *a_room_not_found,
            *w_rank;
  GtkLabel  *w_menu_lbl_userName,
            *w_menu_lbl_score,
            *w_player_1,
            *w_player_2,
            *w_player_3,
            *w_player_4,
            *a_lbl_error,
            *w_lbl_rank[5],
            *w_lbl_score[5],
            *w_lbl_my_rank,
            *w_lbl_my_score;
  GtkButton *w_listRoom_btn_createRoom, 
            *w_listRoom_btn_room[10],
            *w_btn_join_game,
            *w_btn_leave_room,
            *w_btn_send_mess;
  GtkTextView *w_chat_view;
} app_widgets;

typedef struct {
  char *numberOfPlayers;
  char *id;
} room_dto;

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *alert;

int gui(int serverfd);
void *recv_handler(void *app_widget);
gboolean handle_res(app_widgets *widgets);

#endif