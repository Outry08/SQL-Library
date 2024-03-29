CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all : sql

sql : sqllib.c sqllib.h
	$(CC) $(CFLAGS) sqllib.c -o sql

clean:
	- rm *.o sql