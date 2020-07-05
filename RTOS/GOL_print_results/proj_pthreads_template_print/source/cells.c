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

#define LEFT_NEIGHBOUR_ROW(r) (r == 0) ? (config_NE - 1) : (r - 1)
#define RIGHT_NEIGHBOUR_ROW(r) (r == config_NE - 1) ? (0) : (r + 1)
#define TOP_NEIGHBOUR_COL(c) (c == 0) ? (config_ME - 1) : (c - 1)
#define BOTTOM_NEIGHBOUR_COL(c) (c == config_ME - 1) ? (0) : (c + 1)
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
 *     		    a b c
 *              d X e
 *              f g h
 *
 *
 */
size_t countLiveNeighbours(size_t row, size_t col)
{
	// your code goes here

	size_t cell_count = 0;
	size_t neighbour_arr[h_posn + 1];

	neighbour_arr[a_posn] = env[LEFT_NEIGHBOUR_ROW(row)][TOP_NEIGHBOUR_COL(col)];//env[d][b]
	neighbour_arr[b_posn] = env[row][TOP_NEIGHBOUR_COL(col)];
	neighbour_arr[c_posn] = env[RIGHT_NEIGHBOUR_ROW(row)][TOP_NEIGHBOUR_COL(col)];
	neighbour_arr[d_posn] = env[LEFT_NEIGHBOUR_ROW(row)][col];
	neighbour_arr[e_posn] = env[RIGHT_NEIGHBOUR_ROW(row)][col];
	neighbour_arr[f_posn] = env[LEFT_NEIGHBOUR_ROW(row)][BOTTOM_NEIGHBOUR_COL(col)];
	neighbour_arr[g_posn] = env[row][BOTTOM_NEIGHBOUR_COL(col)];
	neighbour_arr[h_posn] = env[RIGHT_NEIGHBOUR_ROW(row)][BOTTOM_NEIGHBOUR_COL(col)];

	for (int i = 0; i <= h_posn; i++)
	{
		cell_count+=neighbour_arr[i];
	}

	#ifdef DEBUG
	printf("returning cell count:%lu \r\n", cell_count);
	#endif
	return cell_count;
}
/*
 * update cell located at row r and column c in env (indicated by X):
 *
 *				a b c
 *				d X e
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
 *
 */

void updateCell(size_t r, size_t c)
{
	cell_t state_cell = env[r][c];
	size_t live_neighbours = countLiveNeighbours(r, c);

	if (state_cell==live)
	{
		if ((live_neighbours >= 4) ||(live_neighbours < 2))
		{
			update_env[r][c]=dead;
		}
	}
	else
	{
		if(live_neighbours==3)
			update_env[r][c]=live;
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
	//  get the cordinates of first cell of community

	#ifdef DEBUG
	printf("thread for r:%lu, c:%lu\r\n", threadid->col, threadid->row);
	#endif
	while(1)
	{
		if(reproduction_flag)
		{

		#ifdef DEBUG
		printf(" row:%lu col:%lu\r\n", threadid->row*config_K, threadid->col*config_L );
		#endif
		// your code goes here
		for (int i = comm_first_row; i < comm_first_row + config_NC; i++)
		{
			for (int j = comm_first_col; j < comm_first_col + config_MC; j++)
			{
				//printf("updating cell r:%lu c:%lu\r\n" ,i,j );
				updateCell(i, j);//config_N
			}
		}
	}
		usleep(config_TL/4);
	}
}
