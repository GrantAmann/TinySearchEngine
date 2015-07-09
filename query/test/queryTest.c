/*======================================================
 * File: queryTest.c - Tiny Search Engine Query
 * Author: Sean Oh
 * Date: May 23, 2015
 *
 * Input: This program will take two inputs.  The first is the index file and the second is the source directory
 *
 * Command line options: n/a
 *
 * Output: This program is unit testing all of the functions that we wrote for query.c so it will print out results from each functions
 *
 *======================================================*/
//---------------------------System includes e.g. <stdio.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

//-------------------------------Local includes e.g.
#include "../src/querylist.h"
#include "../../util/common.h"
#include "../../util/file.h"
#include "../../util/indexhash.h"
#include "../../util/web.h"
#include "../src/query.h"

int main (int argc, char*argv[]){
  printf("testing argcheck...\n");
  if (argcheck(argc,argv) == 1 ){
    exit(1);
  }

  printf("\ntesting addtolist\n");
  printf("adding the word hello\n");
  printf("printing the list\n");
  List *inputList=malloc(sizeof(List));
  inputList->head=NULL;
  inputList->tail=NULL;
  char *newword="hello";
  addtolist(inputList,newword);
  ListNode *printNode=inputList->head;
  printf("%s\n",printNode->word);

  printf("\ntesting insertDocList\n");
  //Take the inverted index and load it into a hashtable                                          
  HashTable *newHash;
  newHash=initializeIndexHash();

  FILE *origfile=fopen(argv[1],"r");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  if (origfile == NULL ){
    printf("Make sure your fourth argument is valid.  Please try again");
    exit(EXIT_FAILURE);
  }
  char *token, *word;
  while ((read = getline(&line,&len,origfile)) != -1 ){
    int wordflag,totflag,IDflag,freqflag;
    wordflag=totflag=IDflag=freqflag=0;
    int IDdoc,freq;

    token = strtok(line," ");
    while ( token != NULL ){
      if(wordflag==0){
	word=token;
	wordflag=1;
	token=strtok(NULL," ");
      }
      if(totflag==0){
	totflag=1;
	token=strtok(NULL," ");
      }
      if(IDflag==0){
	IDflag=1;
	freqflag=1;
	IDdoc=atoi(token);
	token=strtok(NULL," ");
      }
      if(freqflag==1){
	freqflag=0;
	IDflag=0;
	freq=atoi(token);
      }
      char *dummy = malloc((strlen(word)+1)*sizeof(char));
      strncpy(dummy,word,strlen(word)+1);
      insertIndexHash(newHash,dummy,IDdoc,freq);
      token = strtok (NULL, " ");
    }
  }
  free(token);
  free(word);
  fclose(origfile);

  //Initialize a list of docnodes                                                                 
  docList *finalDocs = malloc(sizeof(docList));
  finalDocs->head=NULL;

  printf("\ninserting the word Dartmouth\n");
  char *searchWord="dartmouth";
  finalDocs=insertDocList(newHash,searchWord,finalDocs);
  printf("printing result\n");

  //printing results
  docNode *findnode = finalDocs->head;
  while(findnode != NULL ){
    printf("Document ID: %d  Frequency: %d\n",findnode->doc_id,findnode->freq);
    findnode=findnode->next;
  }

  printf("\ntesting printDocList");
  char *targetdir = argv[2];
  printDocList(finalDocs,targetdir);

  printf("\ntesting sortDocList");
  int docCount=0;
  docNode *countnode = finalDocs->head;
  while(countnode != NULL){
    docCount++;
    countnode=countnode->next;
  }
  sortDocList(finalDocs,docCount);
  printDocList(finalDocs,targetdir);
}
