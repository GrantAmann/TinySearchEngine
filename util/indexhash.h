/* =============================================================================
 * File: indexhash.h
 * 
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * This file contains the definitions for a hashtable of indexes
 *
 * ============================================================================= */
#ifndef HASHTABLE_H
#define HASHTABLE_H

// ---------------------------------Prerequisites e.g. Requires "math.h"
#include "common.h"

// ---------------------------------Constants
#define MAX_HASH_SLOT 10000

// ---------------------------------Structures/Types
// ---------------------------------Public Variables
// ---------------------------------Prototypes/Macros

// Calculates the Jenkins value for the given input
unsigned long JenkinsHash(const char *str, unsigned long mod);

// Initializes the hashtable
HashTable *initializeIndexHash();

// Seaches the hashtable to see if the word has already been added to the hashtable
int searchIndexHash(HashTable *hash, char *targetword);

// Adds a hashtablenode, wordnode, and documentnode for the word found
int insertIndexHash(HashTable *hash, char *targetword, int doc_id, int frequency);

// Clears the hashtable
void freeIndexHash(HashTable *hash);

#endif // HASHTABLE_H



/*
// Initializes the hashtable
HashTable *initializeIndexHash();

// Inserts a word node with a connected document node to the hash table
int insertIndex(HashTable *indexhash, DocumentNode *docNode, char *targetword);

// Inserts a document node to an already existing word node
int insertDoc(DocumentNode *docNode, WordNode *wordNode);

// Searches to see if the word node already exists
WordNode *wordSearch(HashTable *indexhash, char *targetword);

// Searches to see if a document node already exists
DocumentNode *docSearch(WordNode *wordNode, int targetdoc);

// Frees everything that's inside the index hashtable
void freeIndex(HashTable *indexhash);

// Frees all the docnodes in the wordnode
void freelist(WordNode *wordNode);
#endif // HASHTABLE_H
*/
