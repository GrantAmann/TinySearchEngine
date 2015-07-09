#!/bin/bash
test_indexer=./indexerTestlog.`date +"%a_%b_%d_%T_%Y"`
echo "Beginning test of indexer" > $test_indexer
echo "starting at `date +"%H:%M"` on `date +"%m/%d/%Y"`" >> $test_indexer
echo "" >> $test_indexer
echo "clean first..." >> $test_indexer
echo "make clean" >> $test_indexer
make clean

echo "" >> $test_indexer
echo "implementing our Makefile..." >> $test_indexer
echo "make" >> $test_indexer
make

echo "" >> $test_indexer
echo "ex 1. If no arguments are passed with it" >> $test_indexer
echo "indexer" >> $test_indexer
indexer >> $test_indexer
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "ex 2. If not enough arguments are passed with it" >> $test_indexer
echo "indexer blah" >> $test_indexer
indexer blah >> $test_indexer
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "ex 3. If too many arguments are passed with it" >> $test_indexer
echo "indexer data index.dat index.dat new_index.dat blah" >> $test_indexer
indexer data index.dat index.dat new_index.dat blah >> $test_indexer
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "ex 4. If the input for directory is invalid (meaning it doesn't exist)" >> $test_indexer
echo "indexer blah index.dat" >> $test_indexer
indexer blah index.dat >> $test_indexer
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "ex 5. Correct inputs using 3 arguments and the directory data" >> $test_indexer
echo "indexer data index.dat" >> $test_indexer
indexer data index.dat >> $test_indexer

echo "" >> $test_indexer
echo "ex 6. If the target file already exists" >> $test_indexer
echo "indexer data index.dat" >> $test_indexer
indexer data index.dat >> $test_indexer
make clean
make
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "ex 7. Correct inputs using 5 arguments and the directory data" >> $test_indexer
echo "indexer data index.dat index.dat new_index.dat" >> $test_indexer
indexer data index.dat index.dat new_index.dat >> $test_indexer
echo "" >> $test_indexer

echo "" >> $test_indexer
echo "checking to make sure that the first file and second file are the same by running" >> $test_indexer
echo "if cmp -s index.dat new_index.dat" >> $test_indexer
echo "then" >> $test_indexer
echo "   echo The files match " >> $test_indexer
echo "else" >> $test_indexer
echo "   echo The files are different " >> $test_indexer
echo "fi" >> $test_indexer
echo "" >> $test_indexer
echo "running....."  >> $test_indexer
if cmp -s index.dat new_index.dat
then
    echo "The files match" >> $test_indexer
else
    echo "The files are different" >> $test_indexer
fi
make clean
