CC = gcc
CFLAGS=-Wall
LFLAGS=-lncurses -lpthread
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

all: server client clientJoinGame startGame

server: src/server.c
	$(CC) -w -pthread src/server.c src/account.c src/message.c src/room.c src/network.c -o server

client: src/client.c
	$(CC) -w -pthread src/network.c src/message.c src/client.c -o client

startGame: src/startGame.c
	$(CC) $(CFLAGS) src/startGame.c -o startGame $(LFLAGS)

clientJoinGame: src/clientJoinGame.c
	$(CC) $(CFLAGS) src/clientJoinGame.c -o clientJoinGame $(LFLAGS)

ClientGUI.o: src/ClientGUI.c
	$(CC) -c $(CCFLAGS) src/ClientGUI.c $(GTKLIB) -o ClientGUI.o

clean: 
	rm server client clientJoinGame startGame

build: 
	make clean && make all