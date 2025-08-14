CC = $(shell which clang >/dev/null 2>&1 && echo clang || echo gcc)
CFLAGS = -std=c23 -Wall --pedantic-errors -g
LIBS = -lSDL2

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)

clean:
	rm -f main
