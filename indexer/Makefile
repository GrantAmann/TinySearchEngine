# indexer.makefile  
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c11
SRC_DIR = src
FILE_DIR = data

all: indexer

indexer: $(SRC_DIR)/indexer.o $(SRC_DIR)/web.o $(SRC_DIR)/file.o $(SRC_DIR)/indexhash.o
	$(CC) $(CFLAGS) -o indexer $(SRC_DIR)/indexer.o $(SRC_DIR)/web.o $(SRC_DIR)/file.o $(SRC_DIR)/indexhash.o

$(SRC_DIR)/indexer.o: $(SRC_DIR)/indexer.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/indexer.o -c $(SRC_DIR)/indexer.c

$(SRC_DIR)/list.o: $(SRC_DIR)/file.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/file.o -c $(SRC_DIR)/file.c

$(SRC_DIR)/hashtable.o: $(SRC_DIR)/indexhash.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/indexhash.o -c $(SRC_DIR)/indexhash.c

$(SRC_DIR)/web.o: $(SRC_DIR)/web.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/web.o -c $(SRC_DIR)/web.c

.SILENT:

clean:
	rm -f */*~
	rm -f */*.o
	rm -f */*#
	rm -f indexer
	rm -f *~
	rm -f core*
	rm -f *.dat
