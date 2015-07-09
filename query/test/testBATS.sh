#!/bin/bash
test_query=./queryTestlog.`date +"%a_%b_%d_%T_%Y"`
echo "Beginning unit testing of query functions" > $test_query
echo "starting at `date +"%H:%M"` on `date +"%m/%d/%Y"`" >> $test_query
make clean
make
echo "" >> $test_query
echo "queryTest ../../indexer/index.dat ../../crawler/data" >> $test_query
queryTest ../../indexer/index.dat ../../crawler/data >> $test_query
