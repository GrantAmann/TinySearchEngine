# query.makefile
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c11
SRC_DIR = src
FILE_DIR = data

all: query

query: $(SRC_DIR)/query.o $(SRC_DIR)/../../util/web.o $(SRC_DIR)/../../util/file.o $(SRC_DIR)/../../util/indexhash.o $(SRC_DIR)/querylist.o
	$(CC) $(CFLAGS) -o query $(SRC_DIR)/query.c $(SRC_DIR)/../../util/web.o $(SRC_DIR)/../../util/file.o $(SRC_DIR)/../../util/indexhash.o $(SRC_DIR)/querylist.o

$(SRC_DIR)/query.o: $(SRC_DIR)/query.c
	$(CC) $(CFLAGS) -o $(SRC_DIR)/query.o -c $(SRC_DIR)/query.c

$(SRC_DIR)/querylist.o: $(SRC_DIR)/querylist.c 
	$(CC) $(CFLAGS) -o $(SRC_DIR)/querylist.o -c $(SRC_DIR)/querylist.c

$(SRC_DIR)/../../utillist.o: $(SRC_DIR)/../../utilfile.c $(SRC_DIR)/../../utilcommon.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/../../utilfile.o -c $(SRC_DIR)/../../utilfile.c

$(SRC_DIR)/../../utilhashtable.o: $(SRC_DIR)/../../utilindexhash.c $(SRC_DIR)/../../utilcommon.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/../../utilindexhash.o -c $(SRC_DIR)/../../utilindexhash.c

$(SRC_DIR)/../../utilweb.o: $(SRC_DIR)/../../utilweb.c $(SRC_DIR)/../../utilcommon.h
	$(CC) $(CFLAGS) -o $(SRC_DIR)/../../utilweb.o -c $(SRC_DIR)/../../utilweb.c

.SILENT:

clean:
	rm -f */*~
	rm -f */*.o
	rm -f */*#
	rm -f query
	rm -f *~
	rm -f core*
	rm -f vgcore*
