/*
 * gol.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
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
int ENDX = config_NE;
int ENDY = config_ME;
WINDOW *win;
/*
 * main code
 */

void print_disp()
{
	for (int i = 0; i != config_NE; i++)
	{
		for (int j = 0;j < config_ME; j++)
		{
			printf("%u ", env[i][j]);
		}
		printf("\r\n");
	}
}
int main(void)
{
	pthread_t threadptrs[config_K * config_L]; // our thread handles
	threadID_t threadID[config_K * config_L]; // thread ID

	// initialize workspace
	initEnvironment();

	// create the threads
	printf("\n creating threads...\n");
	size_t index;
	for (size_t i = 0; i != config_K; ++i)
	{
		for (size_t j = 0; j != config_L; ++j)
		{
			index = i * config_K + j; // map (i,j) to an 1-d index
			threadID[index].row = i;  //variable of structure "row" and "col"
			threadID[index].col = j;
			printf("index:%lu \r\n", index);
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
	initDisplay();

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
			//printf("*****************\r\n");
			//print_disp();
			//printf("*****************\r\n");
			updateDisplay();
		}
		//printf("copying env now\n");
		copyEnvironment(); // write changes to the environment, env, from update_env
	}

	// should never arrive here;
	return 1;
}
