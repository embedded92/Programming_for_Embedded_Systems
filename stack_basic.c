/*
 * stack_basic.c
 *
 *  Created on: Oct 10, 2019
 *      Author: ramneet
 */
#include<stdlib.h>
#include<stdio.h>
#define L 1024
#define TRUE 1
#define FALSE 0

/*global variables*/
size_t s_top=0;
int s[L];
typedef unsigned short int bool_t;  //type for boolean variable

bool_t stack_empty(void)
{
	if (s_top==0)
		return TRUE;    //return bool_t
	else
		return FALSE;   //return bool_t
}

void push(int x)
{
	s_top++;
	s[s_top]= x;
return;//nothing
}

int pop(void)
{
	if (stack_empty()== TRUE)
		printf("error!! stack is empty!!");
	else
		--s_top;

return s[s_top + 1]; //int type
}

int main()
{
	int loadarr[10]={52, -29, 36,1154,72,0,68,44,33,59}; //array and elements to push and pop on stack

/*load stack*/
	size_t i;
	for(i=0;i!=10; ++i)
	{
		push(loadarr[i]);
	}
/*pop stack*/
	int x;
	while(stack_empty()== FALSE)  //condition to check weather the stack is empty or not
	{
		x=pop();
		printf("%d\n",x);

	}
return EXIT_SUCCESS;

}



