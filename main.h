/* Bilal M Hoor */

#pragma once

#define	NumNode		            10    // Total number of nodes
#define TxCntInit				10		// data frame size in [slot]
#define RxCntInit				2		// ACK frame size in [slot]
#define TotalUnitBOPs			1000000	// SimTime in [slot]

typedef struct node_struct
{
	int Num;				// Node number 
	int k;					// Backoff exponent / initial : k=3/
	int carrier_sensing;	// channel sensing / initial : 1 slot / 
	int BackoffPeriod;		// rand ( 0, 2^BE-1 )
	int State;				// 2: Backoff / 3: sensing / 4: Tx / 5: Rx / 6: TimeOut (no ack received, timeout)
	int TimeOut;

} Node;


void Main_memory_allocation(void);

int main(void);

Node Node_init(Node N, int min_k);

void Main_memory_free(void);
void initialization(void);
void memory_free(void);