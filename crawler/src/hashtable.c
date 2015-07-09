/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * modified by: Sean Oh
 * Date: May 3, 2015
 *
 * The function of this file is to implement hashtable.h and create the functions that were defined in hashtable.h
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>
#include <stdio.h>
// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "hashtable.h"                       // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

//Uses the Jenkins algorithm in order to calculate a unique index number for each url
unsigned long JenkinsHash(const char *str, unsigned long mod)
{
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

//Initialized the hashtable and returns zero if it was a success
HashTable *initializeHashTable(){
  HashTable *hash=(HashTable *)malloc(sizeof(HashTableNode)*MAX_HASH_SLOT);
  int i;
  for(i=0;i<MAX_HASH_SLOT;i++){
    hash->table[i]=NULL;
  }
  return hash;
}

//Goes through the hashtable and checks to see if a certain URL was already added or not. If the URL is free, return that index number, but if it has been used already(meaning the URL is a repeat),return -1
int searchHashTable(HashTable *hash, char *targeturl){
  HashTableNode *findnode;
  int jenkins = JenkinsHash(targeturl,MAX_HASH_SLOT);

  if( hash->table[jenkins] != NULL ){
    findnode=hash->table[jenkins];
    while( findnode != NULL ){
      if( strcmp(findnode->url,targeturl) == 0 ){
	return -1;
      }
      findnode=findnode->next;
    }
  }
  return 0;
}

//Adds a URL into the hashtable as a node.  Will return zero if done correctly
int insertHashTable(HashTable *hash, char *targeturl){
  int jenkins = JenkinsHash(targeturl,MAX_HASH_SLOT);
  if(searchHashTable(hash,targeturl) != 0 ){
    return 1;
  }
  
  HashTableNode *newnode=(HashTableNode *)malloc(sizeof(HashTableNode));
  char *copyurl=(char *)calloc(1,strlen(targeturl)+1);

  strcpy (copyurl,targeturl);
  newnode->url=copyurl;
  newnode->next=NULL;
  
  newnode->next=hash->table[jenkins];
  hash->table[jenkins]=newnode;
  return 0;
}

//Goes through and frees all memory of any hashnodes that were created by us by checking the corresponding URL's and seeing if they contain the initial seed URL that we started with
void freeHashTable(HashTable *hash){
  HashTableNode *node, *dummynode;
  int i;

  if (hash == NULL){
    return;
  }
  
  for(i=0;i<MAX_HASH_SLOT;i++){
    node=hash->table[i];
    while( node != NULL ){
      dummynode=node;
      node=node->next;
      free(dummynode->url);
      free(dummynode);
    }
  }
  free(hash->table);
}
/*
int main(int argc,char* argv[]) {
  HashTable *testhash;
  char * url1;
  url1 = "asdlkfj";
  char * url2;
  url2 = "asldkfjkdlsj";
  int success;
  printf("lahs");
  testhash=initializeHashTable();
  success=insertHashTable(testhash,url1);
  printf("insert jenkins1 %d",success);
  success=insertHashTable(testhash,url2);
  printf("insert jenkins2 %d",success);
  success=insertHashTable(testhash,url1);
  printf("insert jenkins3 %d",success);
  freeHashTable(testhash);
  
}
*/
