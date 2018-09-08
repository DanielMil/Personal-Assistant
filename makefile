CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -c -Iinclude

all: bin/main bin/testMain

bin/menu.o: src/menu.c 
	$(CC) $(CFLAGS) src/menu.c -o bin/menu.o

bin/Assistant.o: src/Assistant.c 
	$(CC) $(CFLAGS) src/Assistant.c -o bin/Assistant.o

bin/TreeAPI.o: src/TreeAPI.c 
	$(CC) $(CFLAGS) src/TreeAPI.c -o bin/TreeAPI.o

bin/main.o: src/main.c include/TreeAPI.h 
	$(CC) $(CFLAGS) src/main.c -o bin/main.o

bin/main: bin/TreeAPI.o bin/main.o  bin/Assistant.o bin/menu.o
	$(CC) bin/TreeAPI.o bin/main.o  bin/Assistant.o bin/menu.o -o bin/runMe

bin/testMain.o: src/testMain.c include/TreeAPI.h 
	$(CC) $(CFLAGS) src/testMain.c -o bin/testMain.o

bin/testMain: bin/TreeAPI.o bin/testMain.o 
	$(CC) bin/TreeAPI.o bin/testMain.o  -o bin/runTest

run:
	./bin/runMe assets/input.txt

runTest:
	./bin/runTest

clean:
	rm bin/*.o
	rm bin/runMe
	rm bin/runTest