/*
 * homework_vector_0.c
 *
 *  Created on: Oct 15, 2019
 *      Author: ramneet
 */
/*
 * standard includes
 */
	#include <stdio.h>
	#include <stdlib.h>
/*
 *  includes for GSL components
 *  	- use double precision
 */
	#include <gsl/gsl_vector_double.h>
	#include <gsl/gsl_matrix_double.h>
	#include <gsl/gsl_rng.h>
	#include <gsl/gsl_randist.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
/*
 * FUNCTIONS
 */

/*
 * simple Fibonacci sequence generator function, using recursion
 * */
size_t fib(size_t k)
{
	if (k==0)
	{
		return 0;
	}
	else if (k==1)
	{
		return 1;
	}
	else /* k >= 2 */
	{
		return fib(k-1) + fib(k-2);
	}
}

int main()
{	/*
	 * INITIALIZE PARAMETERS
	 */
    int N=3;

	/* random number generator parameters */
	const gsl_rng_type *T;
	gsl_rng *r; /* handle for our random number generator */

	/* matrix parameters */
	gsl_matrix *A = gsl_matrix_alloc(N,N);
	gsl_matrix *B = gsl_matrix_alloc(N,N);
	//gsl_matrix *C = gsl_matrix_calloc(N,N);

/*
 * SET UP RANDOM NUMBER GENERATION
 */
	//we need these three lines std practise
	gsl_rng_env_setup();
	T = gsl_rng_default;   //somenthing like macros or in define
	r = gsl_rng_alloc(T);

/*
 * MATRIX OPERATIONS
 */
	//MATRIX A
	int i, j;
	  for (i = 0; i < N; i++)
	    for (j = 0; j < N; j++)
	      {
	    	gsl_matrix_set (A, i, j, fib(i+1));
	    	gsl_matrix_set (B, i, j, gsl_ran_flat(r,-100,+100));
	      }
//Display Matrix A
	  for (i = 0; i < N; i++)  /* OUT OF RANGE ERROR */
	    {
		  for (j = 0; j < N; j++)
	      printf ("A(%d,%d)=%g ", i, j,
	              gsl_matrix_get (A, i, j)) ;
		  printf("\n");
	    }

//Display Matrix B
	  //int k=0;
	  for (i = 0; i < N; i++)  /* OUT OF RANGE ERROR */
	    {
		  for (j = 0; j < N; j++)
	      printf ("B(%d,%d)=%g ", i, j,
	              gsl_matrix_get (B, i, j)) ;
		  printf("\n");

	    }



/* print results */


/* de-allocate memory */
	gsl_matrix_free(A);
	gsl_matrix_free(B);
	//gsl_matrix_free(C);
	return EXIT_SUCCESS;
}

