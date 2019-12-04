/*
 * linked_largest.c
 *
 *  Created on: Oct 3, 2019
 *      Author: ramneet
 */
#include<stdio.h>
#include <stdlib.h>

/*
 * define a linked list node structure
 */
struct linkedList
{
	int		data;
	struct 	linkedList *pNext;
	struct  linkedlist *pPrevious;
};
typedef struct linkedList node_t;

/*
 * define basic functions
 */

node_t*	createNode(void)
{
	/* create a pointer for the new node */
	node_t 	*node;

    /* allocate the node from heap */
    node = 	(node_t *) malloc(sizeof(node_t));

    /* make next point to NULL */
    node -> pNext = NULL;//

    /* return the pointer to the new node */
    return 	node;
}

node_t* addNode(node_t* pHead, int dataval)
{
	/* create two node pointers */
	node_t *node;
	node_t *p;

	/* prepare the new node to be added */
    node = createNode();
    node -> data = dataval; /* set the new element's data field to value */

    if (pHead == NULL)
    {
        pHead = node;     /* if the linked list has no nodes to begin with */
    }
    else
    {
        /* search through list until tail node is found */
        p  = pHead;
        while ((p->pNext) != NULL)
        {
            p = p -> pNext;
        }
        /* set the pointer from NULL to temp */
        p -> pNext = node;
    }
    return pHead;
}

node_t* ListDelete(node_t* pHead, unsigned int key)
{
  // See if we are at end of list.
  if (pHead == NULL)
    return NULL;

   // Check to see if current node is one to be deleted.

  if (pHead->key == key) {
	  node_t*  tempNextP;

    // Save the next pointer in the node.
    tempNextP = pHead->pNext;

    // Deallocate the node.
    free(pHead);

     // Return the NEW pointer
    return tempNextP;
  }

   // Check the rest of the list, in case the next node is the one removed.
  else{pHead->pNext = ListDelete(pHead->pNext, key);

   // Return the pointer
  return pHead;}
}


int main()
{
	int arr[]={56,87,324,2,54,67,21};


	return 0;
}







