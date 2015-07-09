/*
 * File: querylist.c
 *
 * Project name: CS50 tinySearchEngine
 * Component name: query
 * Author: Sean Oh
 * Date: May 20, 2015
 *
 * This file implements the functions declared by querylist.h
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "querylist.h"

//This function initialized the list by setting the head and tail to null
wordList *initializeList(){
  wordList *initlist=(wordList *)malloc(sizeof(wordList));
  initlist->head=NULL;
  initlist->tail=NULL;
  return initlist;
  }

//This function will take the given page and add it as a node to the end of the current list
void addtolist (List *currentlist, char *currentword){
  ListNode *addnode = (ListNode *)malloc(sizeof(ListNode));

  addnode->word=currentword;
  addnode->next=NULL;

  if(currentlist->head == NULL ){
    currentlist->head=addnode;
    currentlist->tail=addnode;
  } else {
    currentlist->tail->next=addnode;
    currentlist->tail=addnode;
  }
}

//This function frees the word list
void freewordlist(wordList *currentlist){
  wordListNode *currnode=currentlist->head;
  wordListNode *temp;
  while( currnode != NULL ){
    WNode *currWnode = currnode->wnode;
    WNode *tempWnode;
      while(currWnode != NULL ){
	tempWnode=currWnode->next;
    free(currWnode->word);
    free(currWnode);
    currWnode=tempWnode;
    }
    temp=currnode->next;
    free(currnode);
  currnode=temp;
  }
  free(currentlist);
}

//This function frees the list
void freelist(List *currentlist){
  ListNode *currnode=currentlist->head;
  ListNode *temp;
  while(currnode!=NULL){
    temp=currnode->next;
    free(currnode->word);
    free(currnode);
    currnode=temp;
  }
  free(temp);
    free(currentlist);
}
