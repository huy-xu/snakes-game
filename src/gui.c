#include "gui.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constant.h"
#include "message.h"
#include "network.h"
#include "request.h"

int gui(int serverfd) {
  pthread_t tid;
  app_widgets *widgets;
  gtk_init(NULL, NULL);
  builder = gtk_builder_new_from_file(GLADE_FILE_NAME);
  widgets = g_slice_new(app_widgets);

  // Get window
  window = GTK_WIDGET(gtk_builder_get_object(builder, WINDOW_MAIN));
  widgets->w_container_feature =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_FEATURE));
  widgets->w_container_listroom =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_LISTROOM));
  widgets->w_container_changepas =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_CHANGEPAS));
  widgets->w_container_menu =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_MENU));
  widgets->w_container_menu_reg =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_MENU_REG));
  widgets->w_container_menu_log =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_MENU_LOG));

  // Get stack
  widgets->w_stack_home =
      GTK_STACK(gtk_builder_get_object(builder, STACK_HOME));
  widgets->w_stack_menu =
      GTK_STACK(gtk_builder_get_object(builder, STACK_MENU));

  // Get entry
  widgets->w_entry_menu_log_user =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_MENU_LOG_USER));
  widgets->w_entry_menu_log_pas =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_MENU_LOG_PAS));

  widgets->serverfd = serverfd;
  widgets->currentWindow = 0;
  gtk_builder_connect_signals(builder, widgets);
  g_object_unref(builder);

  pthread_create(&tid, NULL, &recv_handler, widgets);

  gtk_widget_show(window);
  gtk_main();
  g_slice_free(app_widgets, widgets);

  return 0;
}

void *recv_handler(void *app_widget) {
  int serverfd;
  app_widgets *widgets = (app_widgets *)app_widget;
  Message *response = (Message *)malloc(sizeof(Message));

  pthread_detach(pthread_self());

  serverfd = widgets->serverfd;

  while (1) {
    receiveData(widgets->serverfd, response);
    printf("Server Code: %d\n", response->code);
    g_idle_add((GSourceFunc)handle_res, widgets);
  }

  close(serverfd);
}

gboolean handle_res(app_widgets *widgets) {
  Message *response = (Message *)malloc(sizeof(Message));

  response = widgets->msg;

  printf("%d\n", response->code);
  switch (response->code) {
    case SIGNIN_SUCCESS:
      printf("%d\n", response->code);
      break;

    default:
      printf("Did not handle\n");
      break;
  }

  return FALSE;
}

// called when window is closed
void on_window_main_destroy() { gtk_main_quit(); }

void on_btn_listroom_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_listroom);
  return;
}

void on_btn_backhome_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_feature);
  return;
}

void on_btn_reg_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_feature);
  return;
}

void on_btn_log_clicked(GtkButton *button, app_widgets *app_wdgts) {
  char user[MAX], pass[MAX];

  strcpy(user, gtk_entry_get_text(app_wdgts->w_entry_menu_log_user));
  strcpy(pass, gtk_entry_get_text(app_wdgts->w_entry_menu_log_pas));

  signInReq(app_wdgts->serverfd, user, pass);

  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_feature);
  return;
}
// void on_btn_log_clicked(GtkButton *button, app_widgets *app_wdgts){
//     gtk_stack_set_visible_child(app_wdgts->w_stack_home,
//     app_wdgts->w_container_feature); return;
// }

void on_btn_logout_clicked(GtkButton *button, app_widgets *app_wdgts) {
  signOutReq(app_wdgts->serverfd);

  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_menu);
  gtk_stack_set_visible_child(app_wdgts->w_stack_menu,
                              app_wdgts->w_container_menu_log);
  return;
}

void on_btn_viewchangepas_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_changepas);
  return;
}

void on_btn_changepas_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_menu);
  gtk_stack_set_visible_child(app_wdgts->w_stack_menu,
                              app_wdgts->w_container_menu_log);
  return;
}

void on_btn_changepas_back_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_feature);
  return;
}