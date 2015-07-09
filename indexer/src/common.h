/*===============================================================================
 * File: common.h
 * 
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * This file contains the common defines and data structures..
 *
 *===============================================================================*/
#ifndef COMMON_H
#define COMMON_H

//---------------------------Constants
#define MAX_HASH_SLOT 10000

//---------------------------Structures/Types
typedef struct DocumentNode {
  struct DocumentNode *next;         // pointer to the next member of the list.
  int doc_id;                        // document identifier
  int freq;                          // number of occurrences of the word
} DocumentNode;

typedef struct WordNode {
  struct WordNode *next;            // pointer to the next word (for collisions)
  char *word;                       // the word
  DocumentNode *page;               // pointer to the first element of the page list.
} WordNode;

typedef struct HashTableNode {
  WordNode *data;
  struct HashTableNode *next;
} HashTableNode;

typedef struct HashTable{
  HashTableNode *table[MAX_HASH_SLOT];
} HashTable;

// ---------------- Public Variables
// ---------------- Prototypes/Macros

#endif // COMMON_H
