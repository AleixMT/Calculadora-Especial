CC = gcc
CFLAGS = -O3 -Wall

all : main

calc : main.c
	$(CC) $(CFLAGS) main.c -o main.o

runcalc : main.o
	./main.o

.PHONY : clean
clean :
	rm -f main.o
