/*======================================================================
 * File: query.c - Tiny Search Engine Query
 * Author: Sean Oh
 * Date: May 17, 2015
 *
 * Input: This program will take three inputs including the original command argument.  It will take an index file and a directory that contains files for each url that is searched
 *
 * Command line options: [INDEX FILE] [SOURCE DIRECTORY]
 *
 * Output: Going through the information that is contained in the index file, this program will ask the user for words to search for.  Using the inverse index created and our directory full of files containing urls, the program will output a list of relevant urls in order of search frequency
 *
 * Error Conditions: If the user stops the program using ctrl + d, then the program will bump out of a loop and free all leftover memeory
 *
 *=====================================================================*/
//-------------------------------System includes e.g. <stdio.h>˚
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

//-------------------------------Local includes e.g.
#include "querylist.h"
#include "../../util/common.h"
#include "../../util/file.h"
#include "../../util/indexhash.h"
#include "../../util/web.h"
#include "query.h"
//------------------------------Constant definitions
#define MAX_INPUT 10000
//------------------------------Macro definitions 
int empty = 0;
/* ====================================================================*/

int main (int argc, char *argv[]){
  //Check to make sure that the arguments are valid
  if( argcheck(argc,argv) == 1 ){
    exit(1);
  }
  //Keep asking the user for inputs unless they choose to quit
  while(1){
    char userInput[MAX_INPUT];
    wordList *currlist;

    printf("Please enter the words that you want to search for:");

    //Getting the words and passing them into a list only if the input is not ctrl + d
    if((fgets(userInput,MAX_INPUT,stdin)) != NULL ){
    List *inputList=malloc(sizeof(List));
    inputList->head=NULL;
    inputList->tail=NULL;
    char *tok;
    tok=strtok(userInput," ");
    while( tok != NULL ){
      char *newword = malloc((strlen(tok)+1)*sizeof(char));
      strcpy(newword,tok);
      addtolist(inputList,newword);
      tok=strtok(NULL," ");
    }

    //Making sure that our last word doesn't contain "\n"
    ListNode *fixingnode = inputList->head;
    while( fixingnode->next != NULL ){
      fixingnode=fixingnode->next;
    }
    fixingnode->word[strlen(fixingnode->word)-1]='\0';

    //Initialize our wordlist
    currlist=initializeList();
    wordListNode *newWordListnode = malloc(sizeof(wordListNode));
    newWordListnode->wnode=NULL;
    newWordListnode->next=NULL;
    currlist->head=newWordListnode;
    WNode *newWnode = malloc(sizeof(WNode));
    newWnode->next = NULL;
    newWnode->word=NULL;
    newWordListnode->wnode = newWnode;

    //Go through each word in the line and add it to our list of words
    wordListNode *currWordListNode=currlist->head;
    WNode *currWnode=currlist->head->wnode;

    ListNode *workingnode = inputList->head;
    while( workingnode != NULL ){
      char *word=workingnode->word;

      if( strcmp(word,"OR") == 0 ){
        WNode *freshWnode = malloc(sizeof(WNode));
        freshWnode->next=NULL;
        freshWnode->word=NULL;
        wordListNode *freshWordListNode = malloc(sizeof(wordListNode));
        freshWordListNode->next=NULL;
        freshWordListNode->wnode=NULL;

	currWordListNode->next=freshWordListNode;
        currWordListNode=currWordListNode->next;
        currWordListNode->wnode=freshWnode;
        currWnode=currWordListNode->wnode;
      } else if (strcmp(word," ") == 0){
      } else if ( strcmp(word,"AND") != 0 ){

        //Normalize all of the words before adding them
        for(int j=0;word[j];j++){
          word[j]=tolower(word[j]);
        }

        WNode *freshWnode = malloc(sizeof(WNode));
        freshWnode->next=NULL;
        freshWnode->word=NULL;
        currWnode->word=word;
        currWnode->next=freshWnode;
        currWnode=currWnode->next;
      }
      workingnode=workingnode->next;
    }
  
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
    
    //Enter a while loop in order to create our list of docnodes
    wordListNode *searchNode=currlist->head;
    int check = 0;
    //For every wordlist node...
    while( searchNode != NULL ){
      docList *newDocs = malloc(sizeof(docList));
      newDocs->head=NULL;
      WNode *findWNode=searchNode->wnode;
      empty = 0;

      //For every wordnode...
      while( findWNode->word != NULL ){
	char *searchWord=findWNode->word;
	if ( check == 0 ){
	  finalDocs=insertDocList(newHash,searchWord,finalDocs);
	} else {
	  newDocs=insertDocList(newHash,searchWord,newDocs);
	} 
	findWNode=findWNode->next;
      }
    
      //If it is the first time going through, then do nothing, but if this is the second pass, compare the temporary docList with the master docList to see if there are any similarities, in which case you would want to combine them, or if there are any differences, in which case you would want to add them to the back of the mast docList.
      if( check == 0 ){
	check = 1;
      } else {
	docNode *combineNode = newDocs->head;
	while(combineNode != NULL ){
	  int flick = 0;
	  docNode *fixNode=finalDocs->head;

	  //Combining frequencies if the doc_id's are the same
	  while(fixNode != NULL ){
	    if( fixNode->doc_id == combineNode->doc_id){
	      fixNode->freq+=combineNode->freq;
	      flick = 1;
	    }
	    fixNode=fixNode->next;
	  }
	  if(flick == 0){
	    //Adding docNodes to the docList if the doc_id's don't match up
	    docNode *newDocNode=malloc(sizeof(docNode));
	    newDocNode->doc_id=combineNode->doc_id;
	    newDocNode->freq=combineNode->freq;
	    newDocNode->next=NULL;
	    docNode *dummyNode;
	    docNode *endNode=finalDocs->head;
	    while(endNode != NULL ){
	      dummyNode=endNode;
	      endNode=endNode->next;
	    }
	    if (finalDocs->head == NULL ){
	      finalDocs->head=newDocNode;
	    } else {
	      dummyNode->next=newDocNode;
	    }
	  }
	  combineNode=combineNode->next;
	}
      }
      searchNode=searchNode->next;
      freeDocList(newDocs);
    }
      
    //Sort the docs based on frequency scores
     int docCount=0;
    docNode *countnode = finalDocs->head;
    while(countnode != NULL){
      docCount++;
      countnode=countnode->next;
      }
    sortDocList(finalDocs,docCount);
    
    //Print out the results
    char *targetdir = argv[2];
    printDocList(finalDocs,targetdir);

    //clean and free everything
    freeDocList(finalDocs);
    freewordlist(currlist);   
    freeIndexHash(newHash);
    } else { 
      return 0;
    }
  }
}
  
// Checks to make sure that the arguments passed are valid, meaning that the second argument is a valid file and the third argumnent is a valid directory
int argcheck(int argc, char *argv[]){
  //check to make sure that three arguments were passed
  if( argc != 3 ){
    printf("Sorry, make sure that three arguments are passed. Please try again");
    return 1;
  }
  
  //check to make sure that the file exists and can be opened
  FILE *index;
  index = fopen(argv[1],"r");
  if( index == NULL ){
    printf("Sorry, make sure that the file exists and can be opened.  Please try again");
    return 1;
  }
  fclose(index);

  //check to make sure that the directory exists
  struct stat filedir;
  if ( (stat(argv[2],&filedir)) == -1 ){
    printf("Sorry, make sure that the directory exists.  Please try again");
    return 1;
  }

  return 0;
}

//Inserting the words found into a temporary docList that will be used later in order to compose the master docList
docList *insertDocList(HashTable *currHash, char *currWord, docList *currDocs){
  WordNode *findwordnode;
  int jenkins = JenkinsHash(currWord,MAX_HASH_SLOT);

  //If the word does occupy a slot on the hashtable...
  if (currHash->table[jenkins] != NULL ){
    findwordnode=currHash->table[jenkins]->data;
    //while there are still possible words in the hashtable slot...
    while(findwordnode != NULL ){
      //If the word matches our target word
      if( strcmp(findwordnode->word,currWord) == 0 ){
	DocumentNode *findDocumentNode = findwordnode->page;
	//If there are already entries in the docList
	if ( currDocs->head != NULL ){
	  //While there are already DocumentNodes in the docList we are adding to
	  if( empty != 2 ){
	    docList *tempDoclist = malloc(sizeof(docList));
	    docNode *edocNode = malloc(sizeof(docNode));
	    edocNode->next=NULL;
	    tempDoclist->head=edocNode;

	    docNode *tempDocNode = tempDoclist->head;
	    int count = 0;
	    int change = 0;
	    while( findDocumentNode != NULL ){
	      docNode *newDocNode = malloc(sizeof(docNode));
	      newDocNode->doc_id=findDocumentNode->doc_id;
	      newDocNode->freq=findDocumentNode->freq;
	      newDocNode->next=NULL;
	      
	      //If the docList is already populated, simply add on the new docNode to the end of the docList
	      docNode *findnode = currDocs->head;
	      while(findnode != NULL){
		if(newDocNode->doc_id == findnode->doc_id){
		  change=1;
		  if ( count == 0 ){
		    tempDoclist->head->doc_id=newDocNode->doc_id;
		    tempDoclist->head->freq=newDocNode->freq+findnode->freq;
		    count=1;
		  } else {
		    newDocNode->freq+=findnode->freq;
		    tempDocNode->next=newDocNode;
		    tempDocNode=tempDocNode->next;
		  }
		}
		findnode=findnode->next;
	      }
	      //If the doc_id doesn't match with any on the current list, free the list and set to null
	      if( change == 0 ){
		freeDocList(currDocs);
		docList *failedDocs = malloc(sizeof(docList));
		failedDocs->head=NULL;
		empty=2;
		return failedDocs;
		}
	      findDocumentNode = findDocumentNode->next;
	    }
	  return tempDoclist;
	  }
	} else { //If the docList has not been populated once yet create an initial docNode and set it as the head of the docList
	  if ( empty != 2){
	    docNode *emptydocNode = malloc(sizeof(docNode));
	    emptydocNode->next=NULL;
	    currDocs->head=emptydocNode;
	    int flag = 0;
	    while ( findDocumentNode != NULL ){
	      docNode *newDocNode = malloc(sizeof(docNode));
	      newDocNode->doc_id=findDocumentNode->doc_id;
	      newDocNode->freq=findDocumentNode->freq;
	      newDocNode->next=NULL;
	      docNode *findDocNode=currDocs->head;
	      while(findDocNode->next != NULL ){
		findDocNode=findDocNode->next;
	      }
	      if( flag == 0 ){
		currDocs->head->doc_id=newDocNode->doc_id;
		currDocs->head->freq=newDocNode->freq;
		flag = 1;
	      } else {
		findDocNode->next=newDocNode;
	      }
	      findDocumentNode = findDocumentNode->next;
	    }
	  }
	} return currDocs;
      }
      findwordnode=findwordnode->next;
    }
  } 

  //If the hashtable search came up empty, meaning that the word cannot be found in any url, set the docList so it reads NULL
  if(empty == 0 || empty == 2 ) {
    freeDocList(currDocs);
    docList *failedDocs = malloc(sizeof(docList));
    failedDocs->head=NULL;
    empty=2;
    return failedDocs;
    }
return currDocs;
}

//Free all components of the docList, from the docNodes to the actual list itself.
void freeDocList(docList *currDoc){
  docNode *deletenode = currDoc->head;
  docNode *dummy;
  while(deletenode != NULL){
    dummy = deletenode->next;
    free(deletenode);
    deletenode=dummy;
  }
  free(currDoc);
}

//Print out the components of the docList (doc_id, freq, url) for the given searches
void printDocList(docList *currDoc, char *directory){
  docNode *findnode = currDoc->head;
  printf("\n");
  while(findnode != NULL){
    char *line = NULL;
    size_t len = 0;
    char *newfilename=malloc(strlen(directory)+10);
    sprintf(newfilename,"%s/%d",directory,findnode->doc_id);
    FILE *docfile=fopen(newfilename,"r");
    getline(&line,&len,docfile);
    printf("Document ID:%d  Frequency:%d  URL:%s",findnode->doc_id,findnode->freq,line);
    fclose(docfile);
    free(newfilename);
    free(line);
    findnode=findnode->next;
  }
  printf("\n");
}

//Sort the current docList in order using bubble sort such that the high frequency search comes first and the lowest shows last
void sortDocList(docList *currDoc,int count){
  int i,tempfreq,tempdoc;
  for(i=0;i<count;i++){
    docNode *moveNode=currDoc->head;
    while( moveNode->next != NULL ){
      if(moveNode==currDoc->head){
	if ( currDoc->head->freq < currDoc->head->next->freq){

	  tempfreq=currDoc->head->freq;
	  tempdoc=currDoc->head->doc_id;
	  
	  currDoc->head->freq=currDoc->head->next->freq;
	  currDoc->head->doc_id=currDoc->head->next->doc_id;

	  currDoc->head->next->freq=tempfreq;
	  currDoc->head->next->doc_id=tempdoc;
	}
      } else {
	if(moveNode->freq < moveNode->next->freq){
	  tempfreq=moveNode->freq;
	  tempdoc=moveNode->doc_id;
	  
	  moveNode->freq=moveNode->next->freq;
	  moveNode->doc_id=moveNode->next->doc_id;
	  
	  moveNode->next->freq=tempfreq;
	  moveNode->next->doc_id=tempdoc;
	}
      }
      moveNode=moveNode->next;
    }
  }
}
