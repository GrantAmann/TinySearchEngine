/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author:Sean Oh
 * Date:May 6, 2015
 *
 * Input: This program will take three inputs along with the original command argument.  It will take a seed url, a directory name, and the max depth that user wants the program to search to that is an integer between 0 and 4
 *
 * Command line options: [SEED URL] [DIRECTORY] [DEPTH]
 *
 * Output: Going through each of the urls, for each webpage that is "crawled", the program will create a file in the directory that start at 1 and increments up.  The file will have the url at line 1, the depth at line 2, and then the html file starting at line 3
 *
 * Error Conditions: 
 *
 */
/* ========================================================================== */
// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>                           // printf
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>                       // curl functionality
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality
#include "utils.h"                           // utility stuffs

// ---------------- Constant definitions

// ---------------- Macro definitions
#define SLEEPTIME 0
// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes
int argcheck(int argc, char*argv[]);
WebPage *createWebPage(char *url, int d);
int createfile(WebPage *page, char* directory, int filenum);
void parseHTML(WebPage *currpage, List *currlist, HashTable *currhash, int initdepth);

/* ========================================================================== */
int main(int argc, char* argv[]) {
  int filenum=1;
  int initdepth=1;
  // check command line arguments
  if (argcheck(argc,argv) == 1){
    exit(1);
  }

  char *starturl = argv[1];
  char *targetdir = argv[2];
  int depth = atoi(argv[3]);
  
  //initialize our hashtables and url list
  HashTable *myhashtable;
  List *mylist;
  myhashtable=initializeHashTable();
  mylist=initializelist();
  
  // init curl
  curl_global_init(CURL_GLOBAL_ALL);
  
  // setup seed page
  WebPage *startpage = createWebPage(starturl,0);

  // get seed webpage.  If the url is invalid, quit and send an error message.
  if ( GetWebPage(startpage) == 0 ){
    printf("The url that you entered was invalid.  Please try again.");
    free(startpage->html);
    free(startpage);
    exit(1);
  }
    
  // write seed file
  createfile(startpage,targetdir,filenum);
  filenum++;
  
  // add seed page to hashtable
  insertHashTable(myhashtable,startpage->url);

  // extract urls from seed page
  if( depth > 0 ){
    parseHTML(startpage,mylist,myhashtable,initdepth);
   }

  // while there are urls to crawl
  while ( mylist->head != NULL ){
    // get next url from list
    WebPage *nextpage = listpop(mylist);
    int currdepth = nextpage->depth;
 
   // get webpage for url
    // If the url is invalid, quit and free the memory
    if (GetWebPage(nextpage) != 0 ){
      createfile(nextpage,targetdir,filenum);
      filenum++;
      // extract urls from webpage
      if ( currdepth < depth ){
	parseHTML(nextpage, mylist, myhashtable, currdepth+1);
      }
    }
    free(nextpage->html);
    free(nextpage->url);
    free(nextpage);
    sleep(SLEEPTIME);
  }
  // cleanup curl
  free(startpage->html);
  free(startpage);
  freeHashTable(myhashtable);
  freelist(mylist);
  curl_global_cleanup();
  return 0;
}

//This function will take the arguments that were passed with the crawler command and make sure that they are valid inputs.
int argcheck(int argc,char*argv[]){
  // checks to make sure that three additional inputs are passed with the command
  if( argc != 4 ){
    printf("You must have 3 inputs along with the command.  Please try again");
    return 1;
  }
  
  // checks to make sure that the max depth given is a number and is less than or equal to 4
  char *testdepth;
  float depth = strtod(argv[3],&testdepth);
  if( *testdepth != 0 ){
    printf("Please make sure that your third input is an integer");
    return 1;
  }  
  
  if( depth > 4 ){
    printf("The third input must uphold the max depth limit of 4.  Please try again");
    return 1;
  }

  // check to see if the directory exists
  struct stat dircheck;
  if ( (stat(argv[2], &dircheck)) == -1 ) {
    printf("Make sure that the directory exists.  Please try again");
    return 1;
  }

  return 0;
}

//This function will allocate memory and create a WebPage structure for our url
WebPage *createWebPage(char *url, int depth){
  WebPage *startpage = (WebPage *)malloc(sizeof(WebPage));
  startpage->url=url;
  startpage->depth=depth;

  return startpage;
}

//Will take the given webpage, create a file for it, and write the url, current depth, and the html code for that webpage.
int createfile(WebPage *page, char* directory, int filenum){
  char *newfilename=(char *)malloc(strlen(directory)+10);
  sprintf(newfilename,"%s/%d",directory,filenum);
  FILE *newfile;
  newfile=fopen(newfilename,"wb");
  fprintf(newfile,"%s\n%d\n%s\n",page->url,page->depth,page->html);
  fclose(newfile);
  
  free(newfilename);
  return 0;
}

void parseHTML(WebPage *currpage, List *currlist, HashTable *currhash, int initdepth){
  int position = 0;
  char* newurl;// = NULL;
  char *end;
  //Parsed through the HTML file and gets every URL
  while((position=GetNextURL(currpage->html, position, currpage->url, &newurl)) > 0 ){
    //Normalized the URL and if it is bad, it will be freed right away
    if (NormalizeURL(newurl)){
      //Deals with internal references
      if((end=strchr(newurl,'#'))){
	*end='\0';
      }
      // checks to make sure that the URL has the defined domain
      if( strstr(newurl,URL_PREFIX) != NULL ){
	if ( insertHashTable(currhash,newurl) == 0 ){
	  //Creates a new webpage for the found url and adds it to the our List if it successfully adds to the hashtable
	  char* dummyurl = (char *)malloc(strlen(newurl)+1);
	  strcpy(dummyurl,newurl);
	  WebPage *newpage=createWebPage(dummyurl, initdepth);
	  addtolist(currlist,newpage);
	  free(newurl);
	} else free(newurl);
      } else free(newurl);
    } else free(newurl);
  } 
  free(end);
}
