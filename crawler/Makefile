# crawler.makefile
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c11
SRC_DIR = src
FILE_DIR = data

all: crawler
crawler: $(SRC_DIR)/crawler.o $(SRC_DIR)/web.o $(SRC_DIR)/list.o $(SRC_DIR)/hashtable.o
	$(CC) $(CFLAGS) -o crawler $(SRC_DIR)/crawler.o $(SRC_DIR)/web.o $(SRC_DIR)/list.o $(SRC_DIR)/hashtable.o -lcurl

$(SRC_DIR)/crawler.o: $(SRC_DIR)/crawler.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/crawler.o -c $(SRC_DIR)/crawler.c

$(SRC_DIR)/list.o: $(SRC_DIR)/list.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/list.o -c $(SRC_DIR)/list.c

$(SRC_DIR)/hashtable.o: $(SRC_DIR)/hashtable.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/hashtable.o -c $(SRC_DIR)/hashtable.c

$(SRC_DIR)/web.o: $(SRC_DIR)/web.c $(SRC_DIR)/common.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/web.o -c $(SRC_DIR)/web.c

.SILENT:

clean:
	rm -f */*~
	rm -f */*.o
	rm -f */*#
	rm -f crawler
	rm -f *~
	rm -f core*
	rm -rf data
	mkdir data
