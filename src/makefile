CC = gcc
CFLAGS = -O3 -Wall

all : out

out : main.c
	$(CC) $(CFLAGS) main.c -o out

run : out
	./out

.PHONY : clean
clean :
	rm -f out
