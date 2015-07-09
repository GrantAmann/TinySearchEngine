# queryTst.makefile
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c11
FILE_DIR = data

all: queryTest

queryTest: queryTest.o ../../util/web.o ../../util/file.o ../../util/indexhash.o ../src/querylist.o ../src/query.o
	$(CC) $(CFLAGS) -o queryTest queryTest.o ../src/query.o ../../util/web.o ../../util/file.o ../../util/indexhash.o ../src/querylist.o 

queryTest.o: queryTest.c
	$(CC) $(CFLAGS) -o queryTest.o -c queryTest.c

../src/query.o: ../src/query.c 
	$(CC) $(CFLAGS) -o ../src/query.o -c ../src/query.c

../src/querylist.o: ../src/querylist.c
	$(CC) $(CFLAGS) -o ../src/querylist.o -c ../src/querylist.c

../../utillist.o: ../../utilfile.c ../../utilcommon.h
	$(CC) $(CFLAGS) -o ../../utilfile.o -c ../../utilfile.c

../../utilhashtable.o: ../../utilindexhash.c ../../utilcommon.h
	$(CC) $(CFLAGS) -o ../../utilindexhash.o -c ../../utilindexhash.c

../../utilweb.o: ../../utilweb.c ../../utilcommon.h
	$(CC) $(CFLAGS) -o ../../utilweb.o -c ../../utilweb.c

.SILENT:

clean:
	rm -f *~
	rm -f *.o
	rm -f *#
	rm -f queryTest
	rm -f *~
	rm -f core*
	rm -f vgcore*
