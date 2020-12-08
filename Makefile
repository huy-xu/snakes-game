CC = gcc
all: server client

server: server.c
	$(CC) -w server.c message.c room.c network.c -o server

client: client.c
	$(CC) -w -pthread network.c client.c -o client