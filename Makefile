CC = gcc
DEBUG = -g
WARN = -w
PTHREAD = -pthread
CFLAGS = $(DEBUG) $(WARN)
LFLAGS = -lncurses -lpthread
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`

LD = gcc
LDFLAGS = $(PTHREAD) $(GTKLIB) -export-dynamic

all: server client clientJoinGame startGame

server: src/server.c
	$(CC) $(CFLAGS) $(PTHREAD) src/server.c src/account.c src/message.c src/room.c src/network.c -o server

client: src/client.c
	$(CC) $(CFLAGS) src/network.c src/gui.c src/client.c src/request.c -o client $(LDFLAGS)

startGame: src/startGame.c
	$(CC) -Wall src/startGame.c -o startGame $(LFLAGS)

clientJoinGame: src/clientJoinGame.c
	$(CC) $(CFLAGS) -Wall src/helper.c src/clientJoinGame.c -o clientJoinGame $(LFLAGS)

clean: 
	rm server client clientJoinGame startGame 

build: 
	make clean && make all