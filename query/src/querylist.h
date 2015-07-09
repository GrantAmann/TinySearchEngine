/*===============================================================
 * File: querylist.h
 *
 * Project name: CS50 tinySearchEngine
 * Component name: query
 *
 * This file contains the definitions for a list of words
 *
 *===============================================================*/
#ifndef QUERYLIST_H
#define QUERYLIST_H

//--------------------Structures/Types
typedef struct WNode{
  struct WNode *next;
  char *word;
} WNode;

typedef struct ListNode {
  char *word;
  struct ListNode *next;     //pointer to the next node
} ListNode;

typedef struct List{
  ListNode *head;            //"beginning" of the list
  ListNode *tail;            //"end" of the list
} List;

typedef struct wordListNode{
  WNode *wnode;
  struct wordListNode *next;
} wordListNode;

typedef struct wordList{
  wordListNode *head;
  wordListNode *tail;
} wordList;

typedef struct docNode{
  struct docNode *next;
  int doc_id;
  int freq;
} docNode;

typedef struct docList{
  docNode *head;
} docList;

//--------------------Public Variables
//--------------------Prototypes/Macros

//This function initialized the list by setting the head and tail to null
wordList *initializeList();

//This function will take the given page and add it as a node to the end of the current list
void addtolist (List *currentlist, char *currentword);

//This function frees the word list
void freewordlist(wordList *currentlist);

//This function frees the list
void freelist(List *currentlist);
#endif // QUERYLIST_H
