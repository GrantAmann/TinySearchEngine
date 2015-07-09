/*=======================================================================
 * File: indexhash.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 * Author: Sean Oh
 * Date: May 10, 2015
 * 
 * The function of this file is to implement indexhash.h and create the functions that were defined in indexlist.h
 =========================================================================*/
// ---------------- Open Issues
// ---------------- System includes e.g., <stdio.h>
#include <string.h>    // strlen
#include <stdio.h>
#include <stdlib.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"
#include "indexhash.h"
// ---------------- Constant definitions
// ---------------- Macro definitions
// ---------------- Structures/Types
// ---------------- Private variables
// ---------------- Private prototypes

// Calculates the Jenkins value for the given input
unsigned long JenkinsHash(const char *str, unsigned long mod){
  size_t len = strlen(str);
  unsigned long hash, i;
  
  for(hash = i = 0; i < len; ++i)
    {
      hash += str[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
    }
  
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  
  return hash % mod;
}

// Initializes the hashtable
HashTable *initializeIndexHash(){
  HashTable *hash=(HashTable *)malloc(sizeof(HashTableNode)*MAX_HASH_SLOT);
  int i;
  for(i=0;i<MAX_HASH_SLOT;i++){
    hash->table[i]=NULL;
  }

  return hash;
}

// Seaches the hashtable to see if the word has already been added to the hashtable
int searchIndexHash(HashTable *hash, char *targetword){
  WordNode *findwordnode;
  int jenkins = JenkinsHash(targetword,MAX_HASH_SLOT);

  if (hash->table[jenkins] != NULL ){
    findwordnode=hash->table[jenkins]->data;
    while (findwordnode != NULL ){
      // If we find that the word has already been added to our hashtable, return success
      if( strcmp(findwordnode->word,targetword) == 0 ){
	return 0;
      }
      findwordnode=findwordnode->next;
    }
  }
  return -1;
}

// Adds a hashtablenode, wordnode, and documentnode for the word found
int insertIndexHash(HashTable *hash, char *targetword, int targetid, int frequency){
  int jenkins = JenkinsHash(targetword, MAX_HASH_SLOT);
  WordNode *findwordnode;
  //If the word already exists in the hashtable
  if(searchIndexHash(hash,targetword) == 0 ){
    findwordnode=hash->table[jenkins]->data;
    while(findwordnode != NULL ){
      if( strcmp(findwordnode->word,targetword) == 0 ){
	DocumentNode *finddoc=findwordnode->page;
	DocumentNode *dummydoc=finddoc;
	while(finddoc != NULL ){
	  dummydoc=finddoc;
	  //If the docnode already exists w/ the same doc_id, just increase freq by one
	  if ( finddoc->doc_id == targetid ){
	    (finddoc->freq)++;
	    free(targetword);
	    return 0;
	  }
	  finddoc=finddoc->next;
	}
	// If no doc_id's match, make a new docnode for the given word and target id
	DocumentNode *newDocNode=(DocumentNode *)malloc(sizeof(DocumentNode));
	newDocNode->next=NULL;
	newDocNode->doc_id=targetid;
	newDocNode->freq=frequency;
	dummydoc->next=newDocNode;
	free(targetword);
	return 0;
      }
      findwordnode=findwordnode->next;
    }
  } else {
    // If the word is not in the hashtable, make a wordnode and docnode for it
    DocumentNode *newDocNode=(DocumentNode *)malloc(sizeof(DocumentNode));
    newDocNode->next=NULL;
    newDocNode->doc_id=targetid;
    newDocNode->freq=frequency;

    WordNode *newWordNode=(WordNode *)malloc(sizeof(WordNode));
    newWordNode->next=NULL;
    newWordNode->word=targetword;
    newWordNode->page=newDocNode;

    HashTableNode *newHashNode=(HashTableNode *)malloc(sizeof(HashTableNode));
    newHashNode->data=newWordNode;
    
    if (hash->table[jenkins] != NULL ){
      findwordnode=hash->table[jenkins]->data;
      WordNode *holdernode=findwordnode;
      while (findwordnode != NULL ){
	holdernode=findwordnode;
	findwordnode=findwordnode->next;
      }
      holdernode->next=newWordNode;
      free(newHashNode);
      return 0;
    } else {
      hash->table[jenkins]=newHashNode;
      return 0;
    }
  }
  return 0;
}
// Clears the hashtable
void freeIndexHash(HashTable *hash){
  // If the hashtable is already empty, then return 
  if( hash == NULL ){
    free(hash);
    return;
  }
  
  HashTableNode *node;
  int i;
  
  for(i=0;i<MAX_HASH_SLOT;i++){
    if(hash->table[i]){
      node=hash->table[i];
      HashTableNode *dummynode=node;
      WordNode *wordNode=dummynode->data;
      while( wordNode != NULL ){
	WordNode *dummywordnode=wordNode;
	wordNode=wordNode->next;
	DocumentNode *docNode=dummywordnode->page;
	while( docNode != NULL ){
	  DocumentNode *dummydocnode=docNode;
	  docNode=docNode->next;
	  free(dummydocnode);
	}
	free(dummywordnode->word);
	free(dummywordnode);
      }
      free(dummynode);
    }
  }
  free(hash->table);
 }

/*
int main(int argc,char* argv[]) {
  HashTable *testhash;
  char *word1;
  word1 = "apple";
  int target1=1;
  char *word2;
  word2="banana";
  int target2=2;
  int i;

  testhash=initializeIndexHash();
  insertIndexHash(testhash, word1, target1);
  for(i=0; i<MAX_HASH_SLOT; i++){
    if (testhash->table[i] != NULL ){
  printf("\nword: %s doc_id: %d freq: %d",testhash->table[i]->data->word,testhash->table[i]->data->page->doc_id,testhash->table[i]->data->page->freq);
    }
  }
 printf("\n");
  insertIndexHash(testhash,word2,target2);
  for(i=0; i<MAX_HASH_SLOT; i++){
    if (testhash->table[i] != NULL ){
      printf("\nword: %s doc_id: %d freq: %d",testhash->table[i]->data->word,testhash->table[i]->data->page->doc_id,testhash->table[i]->data->page->freq);
    }
  }
  printf("\n");
  insertIndexHash(testhash,word1,target1);
  for(i=0; i<MAX_HASH_SLOT; i++){
    if (testhash->table[i] != NULL ){
      printf("\nword: %s doc_id: %d freq: %d",testhash->table[i]->data->word,testhash->table[i]->data->page->doc_id,testhash->table[i]->data->page->freq);
    }
  }
  printf("\n");

  insertIndexHash(testhash,word1,target2);
}*/
