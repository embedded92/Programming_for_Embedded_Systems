/*
 * cells.c
 *
 *  Created on: May 30, 2020
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/gol_config.h"
#include "../includes/cells.h"

/*
 * declare important variables (defined in main file as global variables)
 */
//extern cell_t **env;
//extern cell_t **update_env;
extern cell_t env[config_NE][config_ME];
extern cell_t update_env[config_NE][config_ME];
extern bool reproduction_flag;

/*
 * PRIVATE FUNCTIONS
 */

/*
 * transfer a single community identified by the block-pair (iT,jT) to env and
 * update_env using data_init[][]
 */
void transferCommunity(size_t iT, size_t jT,
		const cell_t data_init[config_NC][config_MC])
{
	size_t i_0 = iT * config_NC;
	size_t j_0 = jT * config_MC;

	printf("     ... transferring block (%d, %d)\n", (int) (iT + 1),
			(int) (jT + 1));
	// copy this community to each community in env to initialize it
	for (size_t i = 0; i != config_NC; ++i)
	{
		for (size_t j = 0; j != config_MC; ++j)
		{
			env[i_0 + i][j_0 + j] = update_env[i_0 + i][j_0 + j] =
					data_init[i][j];
		}
	}
}

/*
 * function counts the number of live neighbours of a cell located
 * at row r and column c of the env array
 *
 * for reference, neighbours are designated as follows:
 *     			a b c
 *              d X e
 *              f g h
 *
 *
 */
size_t countLiveNeighbours(size_t row, size_t col)
{
	size_t cell_count = 0;
	//printf("input r:%u, c:%u \r\n", row, col);
	// your code goes here
	if ((row != 0) && (row != config_NE) && (col != 0) && (col != config_NE))
	{
		for (int i = row -1 ; i < row + 1; i++)
		{
			for (int j = col -1; j < col + 1; j++)
			{
				//printf("loop r:%u, c:%u\r\n val:%u", row, col, env[i][j]);
				if ((i == row) && (j == col))
				{
					//printf("in continue for i:%u, j:%u\r\n", i,j);
					continue;
				}
				if (env[i][j] == live)
				{
					//printf("addig to live count:%u\r\n", cell_count + 1);
					++cell_count;
				}
			}
		}
	}
	//printf("returning cell count:%u \r\n", cell_count);
	return cell_count;
}

/*
 * update cell located at row r and column c in env (indicated by X):
 *
 *				d X e
 *				a b c
 *				f g h
 *
 * with nearest neighbours indicated as shown from a, b, ..., h.
 *
 * this function features Conway's rules:
 * 		- if a cell is dead but surrounded by exactly three live neighbours, it sprouts to life (birth)
 * 		- if a cell is live but has more than 4 live neighbours, it dies (overpopulation)
 * 		- if a cell is live but has fewer than 2 live neighbours, it dies (underpopulation)
 * 		- all other dead or live cells remain the same to the next generation (i.e., a live cell must
 * 		  have exactly three neighbours to survive)
 */
void updateCell(size_t r, size_t c)
{
	cell_t state_cell = env[r][c];
	//printf("val :%u \r\n", env[r][c]);
	size_t live_neighbours = countLiveNeighbours(r, c);

	// your code goes here
	if ((state_cell == dead) && (live_neighbours == 3))
	{
		update_env[r][c] = live;
		//printf("1 current dead new live\r\n");
	}
	else if ((state_cell == live) && (live_neighbours > 4))
	{
		update_env[r][c] = dead;
		//printf("2 current live new dead\r\n");
	}
	else if ((state_cell == live) && (live_neighbours < 2))
	{	
		update_env[r][c] = dead;
		//printf("3 current live new dead\r\n");
	}
	

}

/*
 * PUBLIC FUNCTIONS
 */
/*
 * seed environment on a community-by-community basis,
 * from standard input; we assume that the seed input is exactly
 * the size of a community; 9999 indicates end of file;
 * run this before started ncurses environment;
 */
void initEnvironment(void)
{
	// start by reading in a single community
	int token;
	cell_t datum;
	cell_t community_init[config_NC][config_MC];

	printf("\ninitializing environment...\n");
	printf("     ... loading template community from stdin\n");
	for (size_t i = 0; i != config_NC; ++i)
	{
		for (size_t j = 0; j != config_MC; ++j)
		{
			scanf("%d", &token);
			datum = (cell_t) token;
			community_init[i][j] = datum;
		}
	}
	printf("     ... done.\n");

	printf("     ... creating communities\n");
	// copy this community to each community in env to initialize it
	for (size_t i = 0; i != config_K; ++i)
	{
		for (size_t j = 0; j != config_L; ++j)
		{
			transferCommunity(i, j, community_init);
		}
	}
	printf("     ... done.\n");

}
/*
 * write changes to the environment, env, from update_env
 */
void copyEnvironment(void)
{
	// copy this community to each community in env to initialize it
	for (size_t i = 0; i != config_NE; ++i)
	{
		for (size_t j = 0; j != config_ME; ++j)
		{
			env[i][j] = update_env[i][j];
		}
	}
}

/*
 * this function updates all the cells for a thread (corresponding to one community)
 */
void* updateCommFunc(void *param)
{
	threadID_t* threadid = (threadID_t*)param;
	size_t comm_first_col = threadid->col*config_MC;
	size_t comm_first_row = threadid->row*config_NC;
	//  get the coordinates of first cell of community
	//0,0, 3,0, 0,3, 3,3
	
	//printf("thread for r:%u, c:%u\r\n", threadid->col, threadid->row);
	while(1)
	{
		//printf(" row:%u col:%u\r\n", threadid->row*config_K, threadid->col*config_L );
		//printf("in thr funcfor r%u, c:%u\r\n", threadid->row, threadid->col);
		//printf("inside thread func: r:%u, c:%u \r\n", threadid[0].row, threadid[0].col);
		// your code goes here
		for (int i = comm_first_row; i < comm_first_row + config_NC; i++)
		{
			for (int j = comm_first_col; j < comm_first_col + config_MC; j++)
			{
				//printf("updating cell r:%u c:%u\r\n" ,i,j );
				updateCell(i, j);
			}
		}
		usleep(10);
	}
}
