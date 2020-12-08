CC = gcc
all: server client

server: server.c
	$(CC) -w -o server server.c

client: client.c
	$(CC) -w -pthread -o client client.c