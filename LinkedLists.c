/******************************************************************************
* LinkedLists.C - Lydia Hays
* lmh7513@rit.edu
*
* An implementation of doubly linked lists that holds elements containing
* a 256 character string and a sequence number.
* 09/12/2015 - R. Repka     - Improved error checking
* 03/16/2015 - R. Repka     - Added malloc/free debug macros
* 10/10/2016 - R. Repka     - Made macros more clever.  Simple macros are ok too
* 07/21/2017 - R. Repka     - Added class errors
* 12/24/2017 - R. Repka     Removed AddToFrontOfLinkedList()
* 03/12/2018 - R. Repka     Added pseudo code 
* 06/14/2019 - R. Repka     Simplified data structures
* 09/26/2019 - R. Repka     Added comments to RemoveFromFrontOfLinkedList()
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ClassErrors.h"
#include "LinkedLists.h"


/******************************************************************************
  Pseudo code: 
  
  add 1st node
    LinkedList front = points to node 1,  LinkedList back = points to node 1
      Node 1 next     = NULL  (at the end)
      Node 1 previous = NULL (at the start)
          
  add 2nd node
    LinkedList front = points to node 1,  LinkedList back = points to node 2
      Node 1 next points to node 2             Node 2 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)    Node 2 previous points to node 1

  add 3rd node
  LinkedList front = points to node 1,  LinkedList back = points to node 3
      Node 1 next points to node 2           Node 2 next points to node 3      Node 3 next   = NULL  (at the end)
      Node 1 previous = NULL (at the start)  Node 2 previous points to node 1  Node 3 previous points to node 2

   Note: It is possible to implement with only 2 special cases 
      
   Remove from front of 3 node list 
    save the pointer to the data and return it at the end
    LinkedList front = points to node 2,  LinkedList back = points to node 3
      Node 2 next points to node 3           Node 3 next   = NULL  (at the end)
      Node 2 previous = NULL (at the start)  Node 3 previous points to node 2
      free Node but NOT the data
******************************************************************************/

/******************************************************************************
 Initialize the linked list data structure.   Points to nothing, no entries.

 Where: LinkedLists *ListPtr - Pointer to the linked list to create
 Returns: nothing
 Errors: none
******************************************************************************/
void InitLinkedList(LinkedLists *ListPtr)
{
    ListPtr->NumElements = 0;
    ListPtr->FrontPtr = NULL;
    ListPtr->BackPtr = NULL;
}


/******************************************************************************
 Adds a node to the back of the list.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to add to
        char *DataPtr - Pointer to the data to add to the list
 Returns: nothing
 Errors: Prints to stderr and exits
******************************************************************************/
void AddToBackOfLinkedList(LinkedLists *ListPtr, char *DataPtr)
{    
    /* Create the new list node */
    LinkedListNodes *NodePtr = NULL;    
    NodePtr = (LinkedListNodes *)malloc(sizeof(LinkedListNodes));
    MALLOC_DEBUG(NodePtr);
    if (NULL == NodePtr)
    {
        fprintf(stderr, "AddToBackOfLinkedList(): malloc() failed in %s line %d!\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(MALLOC_ERROR);
    }

    strncpy(NodePtr->String, DataPtr, MAX_BUFF_LEN);
    NodePtr->Next = NULL;
    NodePtr->Previous = ListPtr->BackPtr;

    /* Fit the new node into the list */
    if (NULL == ListPtr->FrontPtr)
    {
        ListPtr->FrontPtr = NodePtr;
    }
    else
    {
        ListPtr->BackPtr->Next = NodePtr;
    }
    ListPtr->BackPtr = NodePtr;
    ListPtr->NumElements++;
}

/******************************************************************************
 Removes a node from the front of the list and returns a pointer to the node
 data removed. On empty lists should return a NULL pointer.  
 Note: This you will need to malloc a string buffer and copy the data from the
       linked list node before destroying the node.  The calling routine was
       written to free the string so there are no memory leaks

   Linked lists contain nodes, which contain data strings
 
 Where: LinkedLists *ListPtr    - Pointer to the linked list to remove from
 Returns: Pointer to the data removed or NULL for none
 Errors: none
******************************************************************************/
char *RemoveFromFrontOfLinkedList(LinkedLists *ListPtr)
{
    char *TempData = NULL;
    LinkedListNodes *TempNode = NULL;
    TempNode = ListPtr->FrontPtr;
    if(NULL == TempNode)
    {
        return NULL;
    }
    if(1 == ListPtr->NumElements)
    {
        ListPtr->FrontPtr = NULL;
        ListPtr->BackPtr = NULL;
    }
    else
    {
        ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
        ListPtr->FrontPtr->Previous = NULL;
    }
    
    /* Copy the data out */
    TempData = (char *)malloc(MAX_BUFF_LEN);
    MALLOC_DEBUG(TempData);
    if (NULL == TempData)
    {
        fprintf(stderr, "RemoveFromFrontOfLinkedList(): malloc() failed in %s line %d!\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(MALLOC_ERROR);
    }
    strncpy(TempData, TempNode->String, MAX_BUFF_LEN);
    
    
    ListPtr->NumElements--;
    FREE_DEBUG(TempNode);
    return TempData;
}



/******************************************************************************
 De-allocates the linked list and resets the struct fields (in the header) 
 to indicate that the list is empty.

 Where: LinkedLists *ListPtr    - Pointer to the linked list to destroy
 Returns: nothing
 Errors: none
******************************************************************************/
void DestroyLinkedList(LinkedLists *ListPtr)
{
    LinkedListNodes *CurrNode = NULL;
    LinkedListNodes *TempNode = NULL;
    CurrNode = ListPtr->BackPtr;
    while(NULL != CurrNode)
    {        
        TempNode = CurrNode->Previous;
        FREE_DEBUG(CurrNode);
        CurrNode = TempNode;
    }
    ListPtr->NumElements = 0;
    ListPtr->FrontPtr = NULL;
    ListPtr->BackPtr = NULL;
}


/******************************************************************************
 Searches the linked list for a provided word. If found, returns the pointer
 to the element struct. If not found, returns a NULL pointer
 
 Where: LinkedLists *ListPtr - Pointer to the linked list to search
        char *String         - Pointer to the string to search
 Returns: Pointer to the element if found, NULL otherwise
 Errors: none
 * ***************************************************************************/
int SearchList(LinkedLists *ListPtr, char *String)
{
    LinkedListNodes *TempNode = NULL;
    TempNode = ListPtr->FrontPtr;
    while(NULL != TempNode)
    {
        if(!strcmp(String, TempNode->String))
        {
            return(1);
        }
        TempNode = TempNode->Next;
    }
    return(0);
}




