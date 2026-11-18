CC = gcc
CFLAGS = -g -Wall

all: myshell looper

myshell: myshell.c LineParser.c LineParser.h
	$(CC) $(CFLAGS) -o myshell myshell.c LineParser.c

looper: looper.c
	$(CC) $(CFLAGS) -o looper looper.c

clean:
	rm -f myshell looper

.PHONY: all clean
