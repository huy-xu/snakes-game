#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#include "constant.h"
#include "message.h"

// #define GLADE_FILE_NAME "glade/clientGUI.glade"
#define GLADE_FILE_NAME "glade/nam.glade"
#define GLADE_CSS "glade/style.css"

// ID Window
#define WINDOW_MAIN "window_main"

// ID Stack
// #define STACK_CONTAINER "stack_container"
// #define STACK_MENU "stack_menu"
#define STACK_HOME "stack_home"
#define STACK_MENU "stack_menu"

// ID Container
#define CONTAINER_MENU "container_menu"
#define CONTAINER_FEATURE "container_feature"
#define CONTAINER_LISTROOM "container_listroom"
#define CONTAINER_CHANGEPAS "container_changepas"
#define CONTAINER_MENU_LOG "container_menu_log"
#define CONTAINER_MENU_REG "container_menu_reg"
#define CONTAINER_ROOMVIEW "container_roomview"
#define NUMBER_OF_CONTAINER 6

// ID Entry
#define ENTRY_MENU_LOG_USER "entry_menu_log_user"
#define ENTRY_MENU_LOG_PAS "entry_menu_log_pas"
#define ENTRY_CHANGEPAS_CURPAS "entry_changepas_currpas"
#define ENTRY_CHANGEPAS_NEWPAS "entry_changepas_curpas"
#define ENTRY_CHANGEPAS_CONFIRM "entry_changepas_confirm"

// ID Clickable Button
#define BTN_MENU_REG "btn_menu_log_reg"
#define BTN_LISTROOM_CREATE_ROOM "btn_create_room"
#define BTN_JOIN_GAME "btn_join_game"
#define BTN_LEAVE_ROOM "btn_leave_room"

// ID label
#define LBL_USER_NAME "lbl_user_name"
#define LBL_SCORE "lbl_score"
#define LBL_PLAYER_1 "player_name_1"
#define LBL_PLAYER_2 "player_name_2"
#define LBL_PLAYER_3 "player_name_3"
#define LBL_PLAYER_4 "player_name_4"

typedef struct {
  int currentWindow;
  int serverfd;
  Message *msg;

  GtkEntry  *w_entry_menu_log_user, 
            *w_entry_menu_log_pas,
            *w_entry_changepas_currpas,
            *w_entry_changepas_curpas,
            *w_entry_changepas_confirm;
  GtkStack  *w_stack_home, *w_stack_menu;
  GtkWidget *w_container_feature, 
            *w_container_listroom, 
            *w_container_menu, 
            *w_container_menu_reg, 
            *w_container_menu_log, 
            *w_container_changepas,
            *w_roomView;
  GtkLabel  *w_menu_lbl_userName,
            *w_menu_lbl_score,
            *w_player_1,
            *w_player_2,
            *w_player_3,
            *w_player_4;
  GtkButton *w_listRoom_btn_createRoom, 
            *w_listRoom_btn_room[10],
            *w_btn_join_game,
            *w_btn_leave_room;
} app_widgets;

typedef struct {
  char *numberOfPlayers;
  char *id;
} room_dto;

GtkBuilder *builder;
GtkWidget *window;

int gui(int serverfd);
void *recv_handler(void *app_widget);
gboolean handle_res(app_widgets *widgets);

#endif