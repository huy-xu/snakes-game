CC = gcc
all: server client

server: server.c
	$(CC) -w -pthread server.c message.c room.c network.c -o server

client: client.c
	$(CC) -w -pthread network.c client.c -o client

clean: 
	rm server client

build: 
	make clean && make all