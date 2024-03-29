/*
 * gol.c
 *
 *  Created on: May 30, 2020
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <ncurses.h>
#include "../includes/gol_config.h"
#include "../includes/cells.h"
#include "../includes/display.h"

/*
 * global variables
 */
cell_t env[config_NE][config_ME];
cell_t update_env[config_NE][config_ME];
bool reproduction_flag = false; // is high when it's mating season

int STARTX = 0;
int STARTY = 0;
int ENDX = config_ME;
int ENDY = config_NE;
WINDOW *win;
/*
 * main code
 */

void printEnvironment(void)
{
	int loop1;
	int loop2;
	printf(
			"--------------------------------------------------------------------\r\n");

	for (loop1 = 0; loop1 < config_NE; loop1++)
	{
		for (loop2 = 0; loop2 < config_ME; loop2++)
		{
			if (env[loop1][loop2] == live)
				printf("*");
			else
				printf(" ");
		}
		printf("\r\n");
	}
	printf("\r\n");
}

int main(void)
{
	pthread_t threadptrs[config_K * config_L]; // our thread handles
	threadID_t threadID[config_K * config_L]; // thread ID

	// initialize workspace
	initEnvironment();

	// create the threads
	printf("\ncreating threads...\n");
	size_t index;
	for (size_t i = 0; i != config_K; ++i)
	{
		for (size_t j = 0; j != config_L; ++j)
		{
			index = i * config_L + j; // map (i,j) to an 1-d index
			threadID[index].row = i;
			threadID[index].col = j;
			// the following if condition returns 0 on the successful creation of each thread:
			if (pthread_create(&threadptrs[index], NULL, &updateCommFunc,
					&threadID[index]) != 0)
			{
				printf("failed to create the thread %d\n", (int) index);
				return 1;
			}
		}
	}

	// initialize display with ncurses
	//initDisplay();

	unsigned short int ctr = 0;
	while (1)
	{
		reproduction_flag = true;
		usleep(config_TL / 2); // allow new generation to check in
		reproduction_flag = false;
		usleep(config_TL / 2); // put a hold on reproduction to update display
		if (++ctr == config_TDISP)
		{
			ctr = 0;
			//updateDisplay();
			printEnvironment();
		}
		copyEnvironment(); // write changes to the environment, env, from update_env
	}

	// should never arrive here;
	return 1;
}
