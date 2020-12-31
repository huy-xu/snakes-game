#include "gui.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "account.h"

void *recv_handler(void *app_widget);

int gui(int serverfd) {
  pthread_t tid;
  app_widgets *widgets;
  gtk_init(NULL, NULL);
  builder = gtk_builder_new_from_file(GLADE_FILE_NAME);
  widgets = g_slice_new(app_widgets);

  // Get window
  window = GTK_WIDGET(gtk_builder_get_object(builder, WINDOW_MAIN));
  widgets->w_container_menu_log =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_MENU_LOG));

  // Get stack
  widgets->w_stack_container =
      GTK_STACK(gtk_builder_get_object(builder, STACK_CONTAINER));
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

void on_btn_menu_login_clicked(GtkButton *button, app_widgets *app_wdgts) {
  char username[MAX], password[MAX];
  char request[MAX];

  strcpy(username, gtk_entry_get_text(app_wdgts->w_entry_menu_log_user));
  strcpy(password, gtk_entry_get_text(app_wdgts->w_entry_menu_log_pas));
  sprintf(request, "signIn-%s-%s", username, password);
  sendData(app_wdgts->serverfd, request);
  
  return;
}

void on_window_main_destroy() { gtk_main_quit(); }

void *recv_handler(void *app_widget) {
  int serverfd;
  char response[MAX];
  app_widgets *widgets = (app_widgets *)app_widget;
  // Response *res = (Response *)malloc(sizeof(Response));

  pthread_detach(pthread_self());
  
  serverfd = widgets->serverfd;

  while (1) {
    receiveData(widgets->serverfd, response);
    printf("%s\n", response);
    // g_idle_add((GSourceFunc)handle_res, widgets);
  }

  close(serverfd);
}