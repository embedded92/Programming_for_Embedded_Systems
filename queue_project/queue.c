/*
 * queue.c
 *
 *  Created on: Oct 17, 2019
 *      Author: ramneet
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define	L	1024
#define	TRUE	1U
#define	FALSE	0U

/*
 * struct and typedef declarations
*/
struct	queue_struct
{
	int	data[L];
	size_t 	tail;
	size_t head;
};

typedef struct queue_struct	queue_t;
typedef unsigned short int	bool_t;

/* *************** FUNCTIONS ***************** */
bool_t	queue_empty(queue_t* q)
{
	if (q -> tail == q -> head)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/**
 * Enqueue/Insert an element to the queue.
 */
int enqueue( queue_t* q, int x)
{
	q-> data[q->tail]=x;
	if (q->tail==L)
	{
		q-> tail=1;
	}
	else
	{
		q->tail=q->tail+1;
	}
}
/**
 * Dequeue/Remove an element from the queue.
 */
 int dequeue(queue_t* q)
{
   int x= q->data[q->head];
if(q->head==L)
    {
    	q->head=1;
    }
    else
    {
    	q->head= q->head+1;
    }
    return x;
}

int main()
{
	/* declare and initialize variables */
	queue_t	queue;
    queue.tail = 0;
	queue.head=queue.tail;

	int queue_arr[10] = {52, -29, 36, 1154, 72,
			    0, 68, 44, 33, 59};

	/* load Queue-array */
	size_t	i;
	for (i=0; i != 10; ++i)
	{
		printf("queue.tail = %zu, ", queue.tail);
		enqueue(&queue, queue_arr[i]);
		printf("enqueue: adding elements in the queue %d\n", queue_arr[i]);
	}
	/*dequeue */
	int x;
	while (queue_empty(&queue) == FALSE)
	{
		printf("queue.head = %zu, ", queue.head);
		x = dequeue(&queue);
		printf("dequeue: dropping element from the queue %d\n", x);
	}

	/* test error function */
	x = dequeue(&queue); /* comment this out to avoid error */

	return EXIT_SUCCESS;

}
