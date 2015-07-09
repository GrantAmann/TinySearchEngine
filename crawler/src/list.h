/* ========================================================================== */
/* File: list.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a doubly-linked list of WebPages.
 *
 */
/* ========================================================================== */
#ifndef LIST_H
#define LIST_H

// ---------------- Prerequisites e.g., Requires "math.h"
#include "common.h"                          // common functionality

// ---------------- Constants

// ---------------- Structures/Types

typedef struct ListNode {
    WebPage *page;                           // the data for a given page
    struct ListNode *prev;                   // pointer to previous node
    struct ListNode *next;                   // pointer to next node
} ListNode;

typedef struct List {
    ListNode *head;                          // "beginning" of the list
    ListNode *tail;                          // "end" of the list
} List;

// ---------------- Public Variables

// ---------------- Prototypes/Macros

//This function initializes the list by setting the head and tail to null
List *initializelist ();

//This function will take the given page and add it as a node to the end of the current list
void addtolist (List *currentlist, WebPage *currentpage);

//This function will take the node at the head of the list and pop off the page that was assigned to it.  It will rearrange the head to point to the next node and free the memory that was originally allocated.
WebPage *listpop (List *currentlist);

//This function will print out all the contents of the list
void listprint(List *currentlist);

void freelist(List *currentlist);
#endif // LIST_H
