CC = gcc
CFLAGS=-Wall
LFLAGS=-lncurses -lpthread

all: server client clientJoinGame startGame

server: server.c
	$(CC) -w -pthread server.c account.c message.c room.c network.c -o server

client: client.c
	$(CC) -w -pthread network.c client.c -o client

startGame: startGame.c
	$(CC) $(CFLAGS) startGame.c -o startGame $(LFLAGS)

clientJoinGame: clientJoinGame.c
	$(CC) $(CFLAGS) clientJoinGame.c -o clientJoinGame $(LFLAGS)

clean: 
	rm server client

build: 
	make clean && make all