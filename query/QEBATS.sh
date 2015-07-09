#!/bin/bash
test_query=./queryTestlog.`date +"%a_%b_%d_%T_%Y"`
echo "Beginning test of query" > $test_query
echo "starting at `date +"%H:%M"` on `date +"%m/%d/%Y"`" >> $test_query
echo "" >> $test_query
echo "clean first...">> $test_query
echo "make clean" >> $test_query
make clean

echo "" >> $test_query
echo "implementing our Makefile...">> $test_query
echo "make">> $test_query
make

echo "">> $test_query
echo "ex 1. If no arguments are passed with it">> $test_query
echo "query">> $test_query
query >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 2. If not enough arguments are passed with it">> $test_query
echo "query blah">> $test_query
query blah >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 3. If too make arguments are passed with it">> $test_query
echo "query blah blah blah blah">> $test_query
query blah blah blah blah >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 5. Invalid file">> $test_query
echo "query blah ../crawler/data">> $test_query
query blah ../crawler/data >> $test_query
echo "" >> $test_query

echo "">> $test_query
echo "ex 6. Invalid directory">> $test_query
echo "query ../indexer/index.dat blah">> $test_query
query ../indexer/index.dat blah >> $test_query
echo "" >> $test_query

echo "">> $test_query
echo "ex 7. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "Dartmouth" >> $test_query
echo "Dartmouth" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "" >> $test_query

echo "">> $test_query
echo "ex 8. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "Dartmouth news" >> $test_query
echo "Dartmouth news" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 9. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "Dartmouth AND news" >> $test_query
echo "Dartmouth AND news" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 10. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "Dartmouth OR news" >> $test_query
echo "Dartmouth OR news" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 11. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "Dartmouth news OR Computer" >> $test_query
echo "Dartmouth news OR Computer" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 12. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "blahblahblah" >> $test_query
echo "blahblahblah" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 13. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "blahblah OR Dartmouth" >> $test_query
echo "blahblah OR Dartmouth" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query

echo "">> $test_query
echo "ex 14. Correct inputs">> $test_query
echo "query ../indexer/index.dat .../crawler/data">> $test_query
echo "or OR and" >> $test_query
echo "or OR and" | query ../indexer/index.dat ../crawler/data >> $test_query
echo "">> $test_query
