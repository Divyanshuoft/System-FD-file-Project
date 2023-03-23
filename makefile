# This file is called Makefile
# for compiling a program using GSL
# Define the compiler to use.
CC = gcc
CFLAGS = -Wall -g
# all: sample3213

sample3213: sample3213.o
	$(CC) $(CFLAGS) -o $@ $<

sample3213.o: sample3213.c sample3213.h
	$(CC) $(CFLAGS) -c $<

sample3213.h:
	touch sample3213.h

clean:
	rm -f sample3213.o sample3213