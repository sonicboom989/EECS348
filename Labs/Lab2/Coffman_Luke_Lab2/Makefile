CC= g++
CFLAGS=-c -Wall

all: main

main: main.o isOdd.o isEven.o
	$(CC) main.o isOdd.o isEven.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

isOdd.o: isOdd.c
	$(CC) $(CFLAGS) -c isOdd.c

isEven.o: isEven.c
	$(CC) $(CFLAGS) -c isEven.c

clean:
	rm -f *.o main

