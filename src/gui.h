#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#include "constant.h"
#include "message.h"

#define GLADE_FILE_NAME "glade/clientGUI.glade"
#define GLADE_CSS "glade/style.css"

// ID Window
#define WINDOW_MAIN "window_main"

// ID Container
#define CONTAINER_MENU "container_menu"
#define CONTAINER_LOG "container_menu_log"
#define NUMBER_OF_CONTAINER 4

// ID Entry
#define ENTRY_MENU_LOG_USER "entry_menu_log_user"
#define ENTRY_MENU_LOG_PAS "entry_menu_log_pas"

// ID Clickable Button
#define BTN_MENU_REG "btn_menu_log_reg"

typedef struct {
  int currentWindow;
  int serverfd;
  Message *msg;

  GtkEntry *w_entry_menu_log_user, *w_entry_menu_log_pas;
  GtkStack *w_stack_container, *w_stack_menu;
  GtkWidget *w_container_menu_log;
} app_widgets;

GtkBuilder *builder;
GtkWidget *window;

int gui(int serverfd);

#endif