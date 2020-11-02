#ifndef _LINKEDLISTS_H_
#define _LINKEDLISTS_H_
/******************************************************************************
* Linked List
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNode
{
  /* Link pointers to other nodes*/
  struct LinkedListNode *Next;
  struct LinkedListNode *Previous;
   
  /* The user information field, pointer to the actual data */
  void * Data;
} LinkedListNode_t;

typedef struct LinkedList
{
   /* Number of elements in the list */
   int NumElements;
   
   /* Pointer to the front of the list of elements, possibly NULL */
   struct LinkedListNode *FrontPtr;
   
   /* Pointer to the end of the list of elements, possibly NULL */
   struct LinkedListNode *BackPtr;
} LinkedList_t;

void InitLinkedList(LinkedList_t *ListPtr);
void AddToBackOfLinkedList(LinkedList_t *ListPtr, void *DataPtr);
void *RemoveFromFrontOfLinkedList(LinkedList_t *ListPtr);
void DestroyLinkedList(LinkedList_t *ListPtr);

#endif
