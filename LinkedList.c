/******************************************************************************
* LinkedLists.C
******************************************************************************/
#include "LinkedList.h"

void InitLinkedList(LinkedList_t *ListPtr)
{
    ListPtr->NumElements = 0;
    ListPtr->FrontPtr = NULL;
    ListPtr->BackPtr = NULL;
}


void AddToBackOfLinkedList(LinkedList_t *ListPtr, void *DataPtr)
{    
    /* Create the new list node */
    LinkedListNode_t *NodePtr = (LinkedListNode_t *)malloc(sizeof(LinkedListNode_t));
    if (NodePtr == NULL)
    {
        fprintf(stderr, "AddToBackOfLinkedList(): malloc() failed in %s line %d!\n", __FILE__, __LINE__);
        fflush(stderr);
        exit(-1);
    }

    NodePtr->Data = DataPtr;
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


void *RemoveFromFrontOfLinkedList(LinkedList_t *ListPtr)
{
    void *TempData = ListPtr->FrontPtr->Data;
    LinkedListNode_t *TempNode = NULL;
    TempNode = ListPtr->FrontPtr;
    if(TempNode == NULL)
    {
        return NULL;
    }

    if(ListPtr->NumElements == 1)
    {
        ListPtr->FrontPtr = NULL;
        ListPtr->BackPtr = NULL;
    }
    else
    {
        ListPtr->FrontPtr = ListPtr->FrontPtr->Next;
        ListPtr->FrontPtr->Previous = NULL;
    }
    
    free(TempData);
    ListPtr->NumElements--;

    return TempData;
}


void DestroyLinkedList(LinkedList_t *ListPtr)
{
    LinkedListNode_t *CurrNode = NULL;
    LinkedListNode_t *TempNode = NULL;
    CurrNode = ListPtr->BackPtr;
    while(NULL != CurrNode)
    {        
        TempNode = CurrNode->Previous;
        free(CurrNode->Data);
        free(CurrNode);
        CurrNode = TempNode;
    }

    ListPtr->NumElements = 0;
    ListPtr->FrontPtr = NULL;
    ListPtr->BackPtr = NULL;
}

int main(void)
{
    return -1;
}


