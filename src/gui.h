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
#define NUMBER_OF_CONTAINER 6

// ID Entry
#define ENTRY_MENU_LOG_USER "entry_menu_log_user"
#define ENTRY_MENU_LOG_PAS "entry_menu_log_pas"

// ID Clickable Button
#define BTN_MENU_REG "btn_menu_log_reg"

typedef struct {
  int currentWindow;
  int serverfd;
  Message *msg;

  GtkEntry  *w_entry_menu_log_user, *w_entry_menu_log_pas;
  GtkStack  *w_stack_home, *w_stack_menu;
  GtkWidget *w_container_feature, *w_container_listroom, *w_container_menu, *w_container_menu_reg, *w_container_menu_log, *w_container_changepas;
} app_widgets;

GtkBuilder *builder;
GtkWidget *window;

int gui(int serverfd);
void *recv_handler(void *app_widget);
gboolean handle_res(app_widgets *widgets);

#endif