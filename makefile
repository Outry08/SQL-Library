CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all : cql

cql : sqllib.c sqllib.h
	$(CC) $(CFLAGS) sqllib.c -o cql -lsqlite3

clean:
	- rm *.o cql

## leaks --atExit -- ./cql 