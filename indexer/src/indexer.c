/*=========================================================================
 * File: indexer.c - Tiny Search Engine Indexer
 1;2c* 
 * Author: Sean Oh
 * Date: May 10, 2015
 *
 * Input:
 *
 * Commond line options: 
 *
 * Output:
 *
 * Error Conditions:
 *
 *========================================================================*/
//-------------------------------System includes e.g. <stdio.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

//-------------------------------Local includes e.g. 
#include "file.h"
#include "common.h"
#include "indexhash.h"
#include "web.h"

//------------------------------Constant definitions
//------------------------------Macro definitions

int argcheck(int argc, char *argv[]);
int printtofile(HashTable *currhash,char *filename);

/*=======================================================================*/
int main(int argc, char* argv[]) {
  // Check to make sure that the correct number of arguments were passed with the command
  if( argcheck(argc,argv) == 1 ){
    exit(1);
  }
  
  // Check to make sure there are files in the directory passed
  int filetotal;
  char **filenames=NULL;
  if( (filetotal=GetFilenamesInDir(argv[1],&filenames)) <= 0 ){
    printf("Sorry, the directory you gave had no files.  Please try again");
    exit(1);
  }

  // Initialize the hashtable that we are going to use
  int i;
  HashTable *indexHash;
  indexHash=initializeIndexHash();

  // Go through every file and read the html files 
  for(i=0;i<filetotal;i++){
    int docID=atoi(filenames[i]);

    //Create a char that holds the html info for each file
    char *html;
    long input_file_size;
    FILE *currfile;
    char *newfilename=malloc(strlen(argv[1])+10);
    sprintf(newfilename,"%s/%s",argv[1],filenames[i]);
    currfile=fopen(newfilename,"rb");
    fseek(currfile,0,SEEK_END);
    input_file_size = ftell(currfile);                                                           
    fseek(currfile,0,SEEK_SET);
    
    // Deals with the fact that the first two lines are not part of the html we need
    int count=0;
    char character=getc(currfile);    
    while ( character != '\n' && character != EOF ){
      character=getc(currfile);
      count++;
    }
    fseek(currfile,count,SEEK_SET);
    while ( character != '\n' && character != EOF ){
      character=getc(currfile);
      count++;
    }
    fseek(currfile,count,SEEK_SET);

    //Allocates the memory for the html
    html=malloc(input_file_size * (sizeof(char)));
    fread(html,sizeof(char),input_file_size,currfile);
    fclose(currfile);
    free(newfilename);

    //Read each word
    int pos=0;
    char *word;
    while((pos = GetNextWord(html,pos,&word)) != -1 ){
      //Normalize all of the words
      for(int j=0;word[j];j++){
	word[j]=tolower(word[j]);
      }
      
      //Add word to the hashtable
      insertIndexHash(indexHash,word,docID,1);
    }
    free(html);
    free(filenames[i]);
  }

  //Take the hashtable and print it into an inverted index file
    printtofile(indexHash,argv[2]);
  //free everything in the hashtable
    freeIndexHash(indexHash);
    free(filenames);
 
  if(argc == 5){
    //If there are 5 arguments, read the inverted index file and convert it into a hashtable
    HashTable *newHash;
    newHash=initializeIndexHash();

    FILE *origfile=fopen(argv[3],"r");
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

    //Take everything in the converted hashtable and print it to a new inverted index file
    printtofile(newHash,argv[4]);

    //Free the hashtable
    freeIndexHash(newHash);
      }
  return 0;
}

//Checks to make sure that the arguments passed along with the command are valid
int argcheck(int argc, char *argv[]){
  struct stat dircheck;
  if( argc != 3 && argc != 5 ){
    printf("Make sure that you have either 3 or 5 arguments.  Please try again");
    return 1;
  }

  if( (stat(argv[1], &dircheck)) == -1 ) {
    printf("Make sure that the directory exists.  Please try again");
    return 1;
  }

  if (IsFile(argv[2]) != 0){
    printf("Make sure that the file you're writing to doesn't already exist.  Please try again");
    return 1;
  }		   

  if( argc == 5 ){
    if (IsFile(argv[4]) != 0){
      printf("Make sure that the file you're writing to doesn't already exist.  Please try again");
      return 1;
    }
    if (strcmp(argv[2],argv[4]) == 0 ){
      printf("Make sure that your third and fifth arguments are differen file names.  Please try againg");
      return 1;
    }
  }
  return 0;
}

int printtofile(HashTable *currhash,char *filename){
  if( currhash == NULL ){
    return 1;
  }
  
  FILE *newfile;
  newfile = fopen(filename,"w");
  
  int doccount=0;

  for(int i=0;i<MAX_HASH_SLOT;i++){
    HashTableNode *node=currhash->table[i];
    if( node != NULL ){
      WordNode *wordNode=node->data;
      while ( wordNode != NULL ){
	fprintf(newfile,"%s",wordNode->word);
	DocumentNode *docNode=wordNode->page;
	DocumentNode *holdDocNode=docNode;
	while( docNode != NULL ){
	  doccount++;
	  docNode=docNode->next;
	}
	fprintf(newfile," %d",doccount);
	while( holdDocNode != NULL ){
	  fprintf(newfile," %d %d",holdDocNode->doc_id,holdDocNode->freq);
	  holdDocNode=holdDocNode->next;
	}
	doccount=0;
	wordNode=wordNode->next;
	fprintf(newfile,"\n");
      }
      node=node->next;
    }
  }
  fclose(newfile);
  return 0;
}
