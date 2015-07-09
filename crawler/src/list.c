/*
* File: list.c
* 
* Project name: CS50 Tiny Search Engine
* Component name: Crawler
* Author: Sean Oh
* Date: May 2nd, 2015
*
* This file implements the functions declared by list.h
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "web.h"
#include "common.h"

//This function initializes the list by setting the head and tail to null 
List *initializelist (){
  List *initlist=(List *)malloc(sizeof(List));
  initlist->head=NULL;
  initlist->tail=NULL;
  return initlist;
}

//This function will take the given page and add it as a node to the end of the current list
void addtolist (List *currentlist, WebPage *currentpage){
  ListNode *addnode = (ListNode *)malloc(sizeof(ListNode));

  addnode->page=currentpage;
  addnode->next=NULL;
  addnode->prev=NULL;

  if(currentlist->head == NULL ){
    currentlist->head=addnode;
    currentlist->tail=addnode;
  } else {
      addnode->prev=currentlist->tail;
      currentlist->tail->next=addnode;
      currentlist->tail=addnode;
  }
}

//This function will take the node at the head of the list and pop off the page that was assigned to it. It will also rearrange the head to point to the next node and free the memory that was originally allocated.
WebPage *listpop (List *currentlist){
  WebPage *headpage=currentlist->head->page;
  ListNode *oldnode=currentlist->head;
  currentlist->head=currentlist->head->next;
  free(oldnode);
  return headpage;
}

//This function will print out all the contents of the list
void listprint(List *currentlist){
  ListNode *currnode=currentlist->head;
  
  while(currnode != NULL ){
    printf("the url is %s \n",currnode->page->url);
    printf("the html is %s \n",currnode->page->html);
    currnode=currnode->next;
  }
}

void freelist(List *currentlist){
  ListNode *currnode=currentlist->head;
  ListNode *temp;
  while( currnode!= NULL ){
    temp=currnode->next;
    free(currnode->page->html);
    free(currnode->page->url);
    free(currnode->page);
    free(currnode);
    currnode=temp;
  }
  free(currentlist->tail);
  free(currentlist);
}
/*
int main(int argc, char* argv[]) {
  List *testlist=(List *)calloc(1,sizeof(List));
  WebPage *testpage1=(WebPage *)calloc(1,sizeof(WebPage));
  WebPage *testpage2=(WebPage *)calloc(1,sizeof(WebPage));
  testpage1->url="helloURL";
  testpage1->html="helloHTML";
  testpage1->html_len=5;
  testpage1->depth=3;
  
  testpage2->url="byeURL";
  testpage2->html="byeHTML";
  testpage2->html_len=6;
  testpage2->depth=4;

  initializelist(testlist);
  printf("1\n");
  addtolist(testlist,testpage1);
  listprint(testlist);
  printf("2\n");
  addtolist(testlist,testpage2);
  listprint(testlist);
  printf("3\n");
  listpop(testlist);
  listprint(testlist);
  printf("4\n");
  listpop(testlist);
  listprint(testlist);
  free(testlist);
  free(testpage1);
  free(testpage2);  
}
*/
