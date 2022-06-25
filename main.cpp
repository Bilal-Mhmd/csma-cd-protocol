/* Bilal M Hoor */

/* To Dr Mohammed Aldasht */

/* PPU | College of IT and Computer Engineering */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include"csma.h"
#include "operate.h"
#include "rand.h"

Node* N;
int main()
{
	int min_k = 3;	 // K=3
	int max_k = 5;	// K=5
	int carrier_sensing = 1;	//carrier ssensing takes 1 slot
	//int TimeOut = 3;		// time out for ACK takes 3 slots
	int index;

	srand(time_t(NULL));
	initialization();			// Memory allocation for all the used functions.
	for (index = 0; index < NumNode; index++)
	{
		N[index].Num = index + 1;
		N[index] = Node_init(N[index], min_k);
	}

	CSMA_CD(&N[0], min_k, max_k, carrier_sensing);
	memory_free();	// Free the used memories.
	return 0;
}


void Main_memory_allocation(void)
{
	N = (Node*)malloc(NumNode * sizeof(Node));
}

void Main_memory_free(void)
{
	free(N);
}

void initialization(void)
{
	Main_memory_allocation();
}

void memory_free(void)
{
	Main_memory_free();
}

Node Node_init(Node N, int min_k)
{
	N.k = min_k;	// Backoff exponent / initial : min_k = 3/
	N.BackoffPeriod = rand() % (power(2, (N.k)));	// rand ( 0, 2^k-1 )
	N.State = 2;	// 2: Backoff / 3: carrier sensing / 4: Tx / 5: Rx / 6: Timeout (for collision)
	N.TimeOut = 3;
	N.carrier_sensing = 1;
	return N;
}