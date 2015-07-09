/*===========================================================
 * File: query.h
 *
 * Project name: CS50 tinySearchEngine
 * Component name: query
 *
 *===========================================================*/
#ifndef QUERY_H
#define QUERY_H

#include "querylist.h"
#include "../../util/common.h"
#include "../../util/file.h"
#include "../../util/indexhash.h"
#include "../../util/web.h"

//------------------------Public Variables
//------------------------Prototypes/Macros

// Checks to make sure that the arguments passed are valid, meaning that the second argument is a valid file and the third argumnent is a valid directory
int argcheck(int argc, char *argv[]);

//Inserting the words found into a temporary docList that will be used later in order to compose the master docList
docList *insertDocList(HashTable *currHash, char *currWord, docList *currDocs);

//Free all components of the docList, from the docNodes to the actual list itself.
void freeDocList(docList *currDoc);

//Print out the components of the docList (doc_id, freq, url) for the given searches
void printDocList(docList *currDoc,char *directory);

//Sort the current docList in order using bubble sort such that the high frequency search comes first and the lowest shows last
void sortDocList(docList *currDoc,int count);
#endif //QUERY_H
