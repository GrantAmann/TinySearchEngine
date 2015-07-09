#tinySearchEngine.makefile
CC = gcc
CFLAGS = -g -Wall -pedantic -std=c11
SRC_DIR = src
FILE_DIR = data

all: 
	make -C crawler
	make -C indexer
	make -C query

.SILENT:

clean:
	cd crawler && make clean
	cd ..
	cd indexer && make clean
	cd ..
	cd query && make clean
	cd ..
	rm -f *~
