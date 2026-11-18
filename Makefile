CC = gcc
CFLAGS = -g -Wall

all: myshell looper mypipe

myshell: myshell.c LineParser.c LineParser.h
	$(CC) $(CFLAGS) -o myshell myshell.c LineParser.c

looper: looper.c
	$(CC) $(CFLAGS) -o looper looper.c

mypipe: mypipe.c
	$(CC) $(CFLAGS) -o mypipe mypipe.c

clean:
	rm -f myshell looper mypipe

.PHONY: all clean
