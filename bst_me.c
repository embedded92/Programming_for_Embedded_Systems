/*
 * bst_me.c
 *
 *  Created on: Nov 28, 2019
 *      Author: ramneet
 */
#include<stdio.h>
#include<stdlib.h>

struct node_struct_simple
{
unsigned int key;
struct nodestruct_simple *pl;
struct nodestruct_simple *pR;
struct nodestruct_simple *pParent;
};
void main()
{
typedef  struct nodestruct_simple bst_t;

unsigned int loadarry[]={2,7,6,54,83,1,9,22};

bst_t *pHead= NULL;
pHead= createNode();

pHead-> key = loadarry[0];
size_t i;
	for(i=1; i!=(sizeof(loadarry)/sizeof(key)); ++i)
		{
			pHead= addNode(pHead, loadarry[i]);
		}

}

bst_t *createNode(void)
{
bst_t *pNode= bst_t* malloc(sizeof(bst_t));

pNode -> pL= NULL;
pNode -> pR =Null;
pNode -> pParent = NULL;

return pNode;
}

bst_t* addNode(bst_t *pH, key keyval )
{
bst_t *pNew = createNode();

pNew -> key = keyval;
bst_t *ppw =pH;
bst_t *pw =pH;
bool_t = right;

while(pw!= NULL)
{
ppw=pw;
	if(pw -> key> keyval)
	{
		pw=pw -> pR;
		right= true;
	}
	else
	{
		pw=pw -> pL;
		right= false;
	}


if(right)
{
	ppw -> pR =pNew;
}
else
{
	ppw -> pL =pNew;
}
pNew -> pParent =ppW
return pH;
}
}

inorder_tree_traversal(phead)
{
if(pHead!=NULL)
{
inorder_tree_traversal(pHead->pL)
printf("%d", pHead->key);
inorder_tree_traversal(pHead->pR)
}
}
