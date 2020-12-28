CC = gcc
CFLAGS=-Wall
LFLAGS=-lncurses -lpthread
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

all: server client clientJoinGame startGame

server: src/server/server.c
	$(CC) -w -pthread src/server/server.c src/server/account.c src/server/message.c src/server/room.c src/server/network.c -o server

client: src/client/client.c
	$(CC) -w -pthread src/client/network.c src/client/client.c -o client

startGame: src/server/startGame.c
	$(CC) $(CFLAGS) src/server/startGame.c -o startGame $(LFLAGS)

clientJoinGame: src/client/clientJoinGame.c
	$(CC) $(CFLAGS) src/client/clientJoinGame.c -o clientJoinGame $(LFLAGS)

ClientGUI.o: src/ClientGUI.c
	$(CC) -c $(CCFLAGS) src/ClientGUI.c $(GTKLIB) -o ClientGUI.o

clean: 
	rm server client clientJoinGame startGame

build: 
	make clean && make all