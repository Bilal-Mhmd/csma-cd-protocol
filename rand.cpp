#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "rand.h"
#include "main.h"

double* rand_bit;
double NUM_rand_bit;
void Bit_gen_memory_allocation(void)
{
	rand_bit = (double*)malloc(NUM_rand_bit * sizeof(double));
}

void Rand_gen(void)
{
	int i;
	

		/************************************************************
		*               	 data part generation
		************************************************************/

	for (i = 0; i < NUM_rand_bit; i++) {
		rand_bit[i] = (double)rand() / RAND_MAX;			// information bit generation



	}



	

}

void Exp_Rand_gen(double* exp_rand_bit, double Lambda)
{
	int i;
	

		/************************************************************
		*                	 data part generation
		************************************************************/

	Rand_gen();

	for (i = 0; i < NUM_rand_bit; i++) {

		if (rand_bit[i] == 0)
			exp_rand_bit[i] = -(1. / Lambda) * log(1 - 0.11111111);
		else
			exp_rand_bit[i] = -(1. / Lambda) * log(1. - rand_bit[i]);

		

	}

	




}


double Exp_Rand_gen1(double Lambda)
{
	double exp_rand_bit;

	/************************************************************
	*                	 data part generation
	************************************************************/

	Rand_gen();

	
	if (rand_bit[0] == 0)
		exp_rand_bit = -(1. / Lambda) * log(1 - 0.11111111);
	else if (rand_bit[0] == 1)
		exp_rand_bit = 0;
	else
		exp_rand_bit = -(1. / Lambda) * log(1. - rand_bit[0]);
	return exp_rand_bit;
}
/********************************************************
* Memory_free, Initialization, etc.
********************************************************/

void Bit_gen(int* bit_stream, int stream_size)
{
	int i;

	for (i = 0; i < stream_size; i++)
	{
		bit_stream[i] = rand() % 2;
	}
}

void Bit_gen_memory_free(void)
{
	free(rand_bit);
}