CC=gcc
CFLAGS=-I
all: voting
voting: voting initialise.o voter_function.o evm_function.o
	$(CC) -o voting initialise.o voter_function.o evm_function.o -lpthread

initialise.o: initialise.c initialise.h
	$(CC) -c initialise.c -lpthread

voter_function.o: voter_function.c voter_function.h
	$(CC) -c voter_function.c -lpthread

evm_function.o: evm_function.c evm_function.h
	$(CC) -c evm_function.c -lpthread
