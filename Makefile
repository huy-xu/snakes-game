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
	$(CC) $(CFLAGS) src/network.c src/gui.c src/client.c -o client $(LDFLAGS)

startGame: src/startGame.c
	$(CC) -Wall src/startGame.c -o startGame $(LFLAGS)

clientJoinGame: src/clientJoinGame.c
	$(CC) -Wall src/clientJoinGame.c -o clientJoinGame $(LFLAGS)

gui: src/gui.c
	$(CC) -c $(CFLAGS) src/network.c src/gui.c -o gui $(LDFLAGS)

clean: 
	rm server client gui clientJoinGame startGame 

build: 
	make clean && make all