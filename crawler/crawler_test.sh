#!/bin/bash
test_crawler=./crawlerTestlog.`date +"%a_%b_%d_%T_%Y"`
echo "Beginning test of crawler" > $test_crawler
echo "started at `date +"%H:%M"` on `date +"%m/%d/%Y"`" >> $test_crawler

echo "clean first..." >> $test_crawler
make clean

echo "implementing our Makefile..." >> $test_crawler
make 

echo "ex 1. If no arguemnts are passed with it" >> $test_crawler
echo "crawler" >> $test_crawler
crawler >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 2. If not enough arguments are passed with it" >>$test_crawler
echo "crawler www.dartmouth.edu data" >> $test_crawler
crawler www.dartmouth.edu data >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 3: If too many arguments are passed with it" >> $test_crawler
echo "crawler www.dartmouth.edu data 5 help" >> $test_crawler
crawler www.dartmouth.edu data 5 help >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 4: If the input url is not valid" >> $test_crawler
echo "crawler www.lalablahfake.com data 2" >> $test_crawler
crawler www.lalablahfake.com data 2 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 5: If the input for directory is invalid (meaning it doesn't exist)" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse fakedir 2" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse fakedir 2 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 6: If the input for depth is not within 0 and 4" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse data 5">> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse data 5 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 7: If the input for depth is not an integer" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse data hi" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse data hi >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 8: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/ at depth 0" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 0" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 0 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 9: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/ at depth 1" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 1" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 1 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 10: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/ at depth 2" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 2" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ data 2 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 11: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html at depth 0" >> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 0" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 0 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 12: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html at depth 1">> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 1" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 1 >> $test_crawler
make clean
make

echo "">>$test_crawler
echo "ex 13: Correct inputs using http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html at depth 2">> $test_crawler
echo "crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 2" >> $test_crawler
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/wiki/Computer_science.html data 2 >> $test_crawler

echo "">>$test_crawler
echo "checking to make to sure that files are correctly made" >> $test_crawler
echo "ls data | wc -w" >> $test_crawler
ls data | wc -w >> $test_crawler
