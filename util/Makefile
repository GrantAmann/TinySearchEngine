# Makefile for library
CC= gcc
CFLAGS= -Wall -pedantic -std=c99
SOURCES= *.c

make:
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar -cvq libutil.a *.o

.SILENT:

clean:
	rm -f *~
	rm -f *#
	rm  *.o
	rm -f libutil.a
