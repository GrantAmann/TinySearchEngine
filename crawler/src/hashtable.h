/* ========================================================================== */
/* File: hashtable.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a hashtable of urls.
 *
 */
/* ========================================================================== */
#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "common.h"                          // common functionality

// ---------------- Constants
#define MAX_HASH_SLOT 10000                  // number of "buckets"

// ---------------- Structures/Types

typedef struct HashTableNode {
    char *url;                               // url previously seen
    struct HashTableNode *next;              // pointer to next node
} HashTableNode;

typedef struct HashTable {
    HashTableNode *table[MAX_HASH_SLOT];     // actual hashtable
} HashTable;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

/*
 * jenkins_hash - Bob Jenkins' one_at_a_time hash function
 * @str: char buffer to hash
 * @mod: desired hash modulus
 *
 * Returns hash(str) % mod. Depends on str being null terminated.
 * Implementation details can be found at:
 *     http://www.burtleburtle.net/bob/hash/doobs.html
 */
unsigned long JenkinsHash(const char *str, unsigned long mod);

//Initialized the hashtable and returns zero if it was a success
HashTable *initializeHashTable();

//Goes through the hashtable and checks to see if a certain URL was already added or not. If the URL is free, return that index number, but if it has been used already(meaning the URL is a repeat), return -1
int searchHashTable(HashTable *hash, char *targeturl);

//Adds a URL into the hashtable as a node.  Will return zero if done correctly
int insertHashTable(HashTable *hash, char *targeturl);

//Goes through and frees all memory of any hashnodes that were created by us by checking the corresponding URL's and seeing if they contain the initial seed URL that we started with
void freeHashTable(HashTable *hash);
#endif // HASHTABLE_H
