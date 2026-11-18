CC = gcc
CFLAGS = -g -Wall

all: myshell

myshell: myshell.c LineParser.c LineParser.h
	$(CC) $(CFLAGS) -o myshell myshell.c LineParser.c

clean:
	rm -f myshell

.PHONY: all clean
