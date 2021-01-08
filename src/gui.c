#include "gui.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constant.h"
#include "message.c"
#include "message.h"
#include "network.h"
#include "request.h"

char currentUser[MAX];
char listRoom[6][MAX];
char *player[4];
int numberOfRoom = 0;

int gui(int serverfd) {
  pthread_t tid;
  app_widgets *widgets;
  gtk_init(NULL, NULL);
  builder = gtk_builder_new_from_file(GLADE_FILE_NAME);
  widgets = g_slice_new(app_widgets);

  // Get window
  window = GTK_WIDGET(gtk_builder_get_object(builder, WINDOW_MAIN));
  alert = GTK_WIDGET(gtk_builder_get_object(builder, WINDOW_ALERT));
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
  widgets->w_roomView =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_ROOMVIEW));
  widgets->a_room_not_found =
      GTK_WIDGET(gtk_builder_get_object(builder, ALERT_ROOM_NOT_FOUND));
  widgets->w_rank =
      GTK_WIDGET(gtk_builder_get_object(builder, CONTAINER_SHOWRANK));

  // Get stack
  widgets->w_stack_home =
      GTK_STACK(gtk_builder_get_object(builder, STACK_HOME));
  widgets->w_stack_menu =
      GTK_STACK(gtk_builder_get_object(builder, STACK_MENU));
  widgets->a_stack_alert =
      GTK_STACK(gtk_builder_get_object(builder, STACK_ALERT));

  // Get entry
  widgets->w_entry_menu_log_user =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_MENU_LOG_USER));
  widgets->w_entry_menu_log_pas =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_MENU_LOG_PAS));
  widgets->w_entry_changepas_new =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_CHANGEPAS_NEW));
  widgets->w_entry_changepas_confirm =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_CHANGEPAS_CONFIRM));
  widgets->w_entry_chat =
      GTK_ENTRY(gtk_builder_get_object(builder, ENTRY_CHAT));

  // Get label
  widgets->w_menu_lbl_userName =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_USER_NAME));
  widgets->w_menu_lbl_score =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE));
  widgets->w_player_1 =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_PLAYER_1));
  widgets->w_player_2 =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_PLAYER_2));
  widgets->w_player_3 =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_PLAYER_3));
  widgets->w_player_4 =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_PLAYER_4));
  widgets->a_lbl_error = GTK_LABEL(gtk_builder_get_object(builder, LBL_ERROR));
  widgets->w_lbl_rank[0] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_RANK_USER1));
  widgets->w_lbl_rank[1] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_RANK_USER2));
  widgets->w_lbl_rank[2] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_RANK_USER3));
  widgets->w_lbl_rank[3] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_RANK_USER4));
  widgets->w_lbl_rank[4] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_RANK_USER5));
  widgets->w_lbl_score[0] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE1));
  widgets->w_lbl_score[1] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE2));
  widgets->w_lbl_score[2] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE3));
  widgets->w_lbl_score[3] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE4));
  widgets->w_lbl_score[4] =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_SCORE5));
  widgets->w_lbl_my_rank =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_YUOR_RANK));
  widgets->w_lbl_my_score =
      GTK_LABEL(gtk_builder_get_object(builder, LBL_YOUR_SCORE));

  // Get button
  widgets->w_listRoom_btn_room[0] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom1"));
  widgets->w_listRoom_btn_room[1] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom2"));
  widgets->w_listRoom_btn_room[2] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom3"));
  widgets->w_listRoom_btn_room[3] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom4"));
  widgets->w_listRoom_btn_room[4] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom5"));
  widgets->w_listRoom_btn_room[5] =
      GTK_BUTTON(gtk_builder_get_object(builder, "btn_enterroom6"));
  widgets->w_btn_start_game =
      GTK_BUTTON(gtk_builder_get_object(builder, BTN_START_GAME));
  widgets->w_btn_leave_room =
      GTK_BUTTON(gtk_builder_get_object(builder, BTN_LEAVE_ROOM));
  widgets->w_btn_send_mess =
      GTK_BUTTON(gtk_builder_get_object(builder, BTN_SEND_MESS));
  widgets->w_chat_view =
      GTK_TEXT_VIEW(gtk_builder_get_object(builder, TXT_CHAT_VIEW));

  widgets->serverfd = serverfd;
  widgets->currentWindow = 0;
  gtk_builder_connect_signals(builder, widgets);
  g_object_unref(builder);

  pthread_create(&tid, NULL, &recv_handler, widgets);

  gtk_stack_set_visible_child(widgets->w_stack_home, widgets->w_container_menu);
  gtk_stack_set_visible_child(widgets->a_stack_alert,
                              widgets->a_room_not_found);

  gtk_widget_show(window);
  gtk_main();
  g_slice_free(app_widgets, widgets);

  return 0;
}

void *recv_handler(void *app_widget) {
  int serverfd, receiveBytes;
  app_widgets *widgets = (app_widgets *)app_widget;
  Message *response = (Message *)malloc(sizeof(Message));

  pthread_detach(pthread_self());

  serverfd = widgets->serverfd;

  while (1) {
    receiveBytes = receiveData(widgets->serverfd, response);
    if (receiveBytes == 0) {
      break;
    }
    printf("Server Code: %d\nServer data: %s\n\n", response->code,
           response->data);
    widgets->msg = response;
    g_idle_add((GSourceFunc)handle_res, widgets);
  }

  if (receiveBytes == 0) {
    printf("SERVER IS DOWN\n");
    exit(0);
  }

  close(serverfd);
}

gboolean handle_res(app_widgets *widgets) {
  switch (widgets->msg->code) {
    case SIGNIN_SUCCESS: {
      char *argv[2];
      char user[MAX] = "Welcome ";
      char score[MAX] = "Your scores: ";

      splitData(argv, widgets->msg->data);

      strcpy(currentUser, argv[0]);

      strcat(user, argv[0]);
      strcat(user, "!");
      strcat(score, argv[1]);

      gtk_label_set_text(GTK_LABEL(widgets->w_menu_lbl_userName), user);
      gtk_label_set_text(GTK_LABEL(widgets->w_menu_lbl_score), score);
      gtk_stack_set_visible_child(widgets->w_stack_home,
                                  widgets->w_container_feature);
      break;
    }

    case SIGNIN_FAIL: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case SIGNUP_SUCCESS:
      gtk_stack_set_visible_child(widgets->w_stack_menu,
                                  widgets->w_container_menu_log);
      break;

    case SIGNOUT_SUCCESS: {
      gtk_stack_set_visible_child(widgets->w_stack_menu,
                                  widgets->w_container_menu_log);
      break;
    }

    case REPASS_NOT_MATCH: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case ACCOUNT_EXISTED: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case CHANGE_PASSWORD_SUCCESS: {
      gtk_stack_set_visible_child(widgets->w_stack_home,
                                  widgets->w_container_feature);
      break;
    }

    case CHANGE_PASSWORD_FAIL: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case SHOW_RANK_SUCCESS: {
      char tempRank[MAX];
      strcpy(tempRank, widgets->msg->data);
      int numberRank = numOfArgv(tempRank);

      char *rank[6];
      splitData(rank, tempRank);
      char *myScore[2];
      splitData2(myScore, rank[numberRank - 1]);
      char tmpMyRank[MAX] = "#";
      strcat(tmpMyRank, myScore[0]);
      gtk_label_set_text(widgets->w_lbl_my_rank, tmpMyRank);
      gtk_label_set_text(widgets->w_lbl_my_score, myScore[1]);

      for (int i = 0; i < numberRank - 1; i++) {
        char *score[2];
        splitData2(score, rank[i]);
        gtk_label_set_text(widgets->w_lbl_rank[i], score[0]);
        gtk_label_set_text(widgets->w_lbl_score[i], score[1]);
      }
      gtk_stack_set_visible_child(widgets->w_stack_home, widgets->w_rank);
      break;
    }

    case ROOM_NOT_FOUND: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case ROOM_IS_FULL: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case SHOW_ROOM_SUCCESS: {
      numberOfRoom = 0;
      gtk_stack_set_visible_child(widgets->w_stack_home,
                                  widgets->w_container_listroom);
      if (strcmp(widgets->msg->data, "#") == 0) {
        return FALSE;
      }

      char temp[MAX];
      strcpy(temp, widgets->msg->data);
      numberOfRoom = numOfArgv(temp);

      char *rooms[MAX_ROOMS];
      splitData(rooms, temp);

      for (int i = 0; i < numberOfRoom; i++) {
        strcpy(listRoom[i], rooms[i]);
        char *roomInfo[2];
        splitData2(roomInfo, listRoom[i]);
        char roomString[11] = {'R', 'o',     'o', 'm',
                               ' ', i + '0', '(', roomInfo[1][0],
                               '/', '4',     ')'};
        gtk_button_set_label(widgets->w_listRoom_btn_room[i], roomString);
        gtk_widget_show(widgets->w_listRoom_btn_room[i]);
        if (roomInfo[1][0] == '4') {
          gtk_widget_set_sensitive(widgets->w_listRoom_btn_room[i], FALSE);
        }
      }
      break;
    }

    case CREATE_ROOM_SUCCESS: {
      gtk_label_set_text(GTK_LABEL(widgets->w_player_1), currentUser);
      gtk_label_set_text(GTK_LABEL(widgets->w_player_2), "");
      gtk_label_set_text(GTK_LABEL(widgets->w_player_3), "");
      gtk_label_set_text(GTK_LABEL(widgets->w_player_4), "");
      gtk_widget_show(widgets->w_btn_start_game);
      gtk_stack_set_visible_child(widgets->w_stack_home, widgets->w_roomView);
      break;
    }

    case JOIN_ROOM_SUCCESS: {
      char tempRoom[MAX];
      strcpy(tempRoom, widgets->msg->data);
      splitData(player, tempRoom);

      if (player[0] != NULL) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_1), player[0]);
      }
      if (player[1] != NULL) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_2), player[1]);
      }
      if (player[2] != NULL) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_3), player[2]);
      }
      if (player[3] != NULL) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_4), player[3]);
      }
      gtk_widget_hide(widgets->w_btn_start_game);
      gtk_stack_set_visible_child(widgets->w_stack_home, widgets->w_roomView);
      break;
    }

    case LEAVE_ROOM_SUCCESS: {
      gtk_stack_set_visible_child(widgets->w_stack_home,
                                  widgets->w_container_listroom);
      break;
    }

    case PLAYER_LEFT_ROOM: {
      char tempLeftRoom[MAX];
      strcpy(tempLeftRoom, widgets->msg->data);
      if (strcmp(player[0], tempLeftRoom) == 0) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_1), "");
      } else if (strcmp(player[1], tempLeftRoom) == 0) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_2), "");
      } else if (strcmp(player[2], tempLeftRoom) == 0) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_3), "");
      } else if (strcmp(player[3], tempLeftRoom) == 0) {
        gtk_label_set_text(GTK_LABEL(widgets->w_player_4), "");
      }
      break;
    }

    case SIGNIN_OTHER_PC: {
      gtk_label_set_text(widgets->a_lbl_error, widgets->msg->data);
      gtk_widget_show(alert);
      break;
    }

    case CHAT_SUCCESS: {
      char tempChat[MAX];
      strcpy(tempChat, widgets->msg->data);
      GtkTextBuffer *buffer;
      GtkTextMark *mark;
      GtkTextIter iter;
      buffer = gtk_text_view_get_buffer(widgets->w_chat_view);
      mark = gtk_text_buffer_get_insert(buffer);
      gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
      if (gtk_text_buffer_get_char_count(buffer))
        gtk_text_buffer_insert(buffer, &iter, "\n", 1);
      gtk_text_buffer_insert(buffer, &iter, tempChat, -1);
      break;
    }
    case START_GAME_SUCCESS: {
      char clientJoinGame[MAX];
      char serverPort[MAX];

      strcpy(serverPort, widgets->msg->data);

      sprintf(clientJoinGame, "./clientJoinGame %s %s %s", SERVER_IP, serverPort, currentUser);
      system(clientJoinGame);

      break;
    }
  }

  return FALSE;
}

// called when window is closed
void on_window_main_destroy(GtkWidget *widget, app_widgets *app_wdgts) {
  quitGameReq(app_wdgts->serverfd);
  gtk_main_quit();
  return;
}

void on_btn_listroom_clicked(GtkButton *button, app_widgets *app_wdgts) {
  showRoomReq(app_wdgts->serverfd);
  return;
}

void on_btn_refresh_clicked(GtkButton *button, app_widgets *app_wdgts) {
  showRoomReq(app_wdgts->serverfd);
  return;
}

void on_btn_back_clicked(GtkButton *button, app_widgets *app_wdgts) {
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
  return;
}

void on_btn_logout_clicked(GtkButton *button, app_widgets *app_wdgts) {
  signOutReq(app_wdgts->serverfd);
  return;
}

void on_btn_viewchangepas_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_home,
                              app_wdgts->w_container_changepas);
  return;
}

void on_btn_changepas_clicked(GtkButton *button, app_widgets *app_wdgts) {
  char curPas[MAX], newPas[MAX], confirm[MAX];

  strcpy(newPas, gtk_entry_get_text(app_wdgts->w_entry_changepas_new));
  strcpy(confirm, gtk_entry_get_text(app_wdgts->w_entry_changepas_confirm));
  changePasswordReq(app_wdgts->serverfd, newPas, confirm);
  return;
}

void on_btn_createroom_clicked(GtkButton *button, app_widgets *app_wdgts) {
  createRoomReq(app_wdgts->serverfd);
  return;
}

void joinRoom1(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[0]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void joinRoom2(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[1]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void joinRoom3(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[2]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void joinRoom4(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[3]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void joinRoom5(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[4]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void joinRoom6(GtkButton *button, app_widgets *app_wdgts) {
  char *roomInfo[2];
  splitData2(roomInfo, listRoom[5]);
  joinRoomReq(app_wdgts->serverfd, roomInfo[0]);
}

void on_btn_leave_room_clicked(GtkButton *button, app_widgets *app_wdgts) {
  leaveRoomReq(app_wdgts->serverfd);
}

void on_btn_goto_signup_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_menu,
                              app_wdgts->w_container_menu_reg);
}

void on_btn_goto_signin_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_stack_set_visible_child(app_wdgts->w_stack_menu,
                              app_wdgts->w_container_menu_log);
}

void on_btn_send_mess_clicked(GtkButton *button, app_widgets *app_wdgts) {
  char chat[MAX];
  strcpy(chat, gtk_entry_get_text(app_wdgts->w_entry_chat));
  chatRoomReq(app_wdgts->serverfd, chat);
}

void on_btn_ok_1_clicked(GtkButton *button, app_widgets *app_wdgts) {
  gtk_widget_hide(alert);
}

void on_btn_see_rank_clicked(GtkButton *button, app_widgets *app_wdgts) {
  showRankReq(app_wdgts->serverfd);
}

void on_btn_start_game_clicked(GtkButton *button, app_widgets *app_wdgts) {
  startGameReq(app_wdgts->serverfd);
}