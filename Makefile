CC = gcc
DEBUG = -g
WARN = -w
PTHREAD = -pthread
CFLAGS = $(DEBUG) $(WARN)
LFLAGS = -lncurses -lpthread
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`

all: server client clientJoinGame startGame

server: src/server.c
	$(CC) $(CFLAGS) $(PTHREAD) src/server.c src/account.c src/message.c src/room.c src/network.c -o server

client: src/client.c
	$(CC) $(CFLAGS) $(PTHREAD) src/network.c src/client.c -o client

startGame: src/startGame.c
	$(CC) $(CFLAGS) $(LFLAGS) src/startGame.c -o startGame

clientJoinGame: src/clientJoinGame.c
	$(CC) $(CFLAGS) $(LFLAGS) src/clientJoinGame.c -o clientJoinGame

gui: src/gui.c
	$(CC) $(CFLAGS) $(PTHREAD) $(GTKLIB) -c src/gui.c -o gui

clean: 
	rm server client gui clientJoinGame startGame 

build: 
	make clean && make all