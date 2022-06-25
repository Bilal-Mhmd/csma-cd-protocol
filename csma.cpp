#include<stdio.h>
#include <stdlib.h>
#include "csma.h"
#include "operate.h"
#include "rand.h"
#include <math.h>
#include "main.h"

 //counters
int		init[NumNode];			// node initialize indicator
int		nodebusy[NumNode];		//A variable that determines whether the node is busy (1) or idle (0).
int		tx_cnt[NumNode];
int		rx_cnt[NumNode];
int		chbusy = 0;				// Idle 0, busy 1
int		chbusy_cnt = 0;			// To check if there is more than one transmission at the same time
int		tx_failure = 0;			// calculate total failed transmission
int		total_pkt = 0;				// total number of transmission
int     total_suc = 0;
int     trans_attempt = 0;
int     total_colision = 0;

void CSMA_CD(Node* node, int min_k, int max_k, int carrier_sensing)
{
	int i, n;
	tx_failure = 0;        // count total number of failed(collision) transmission
	total_pkt = 0;        // count total number of packet transmission(including successful & failure)
	chbusy = 0;
	chbusy_cnt = 0;
	for (i = 0; i < NumNode; i++)
	{
		nodebusy[i] = 0;			// particular node busy/idle indicator
		init[i] = 0;				// Node has initialized its RANDOM backoff
		tx_cnt[i] = TxCntInit;		// Initialize packet size, e.i, 10 slots
		rx_cnt[i] = RxCntInit;		// Initialize ACK size, e.i, 2 slots
	}

	for (i = 1; i <= TotalUnitBOPs; i++)//TotalUnitBOPs=100000, total simulation time [slots]
	{
		for (n = 0; n < NumNode; n++)
		{
			if (init[n] == 0)		// Node has initialized its RANDOM backoff
			{
				// my Revise Code - initialization
				node[n].k = min_k;    // Backoff exponent / initial : min_k = 3/
				node[n].BackoffPeriod = rand() % (power(2, (node[n].k)));    // rand ( 0, 2^k-1 )
				node[n].TimeOut = 3;
				node[n].carrier_sensing = 1;
				tx_cnt[n] = TxCntInit;
				rx_cnt[n] = RxCntInit;

				// my Revise Code
				if (node[n].BackoffPeriod == 0)
				{
					node[n].State = 3;	// Node should be doing channel sensing right away if there is NO Backoff
				}
				else
				{
					node[n].State = 2;	// Node does not need to be stay in the idle slot, since it ALWAYS HAS packet.
				}
			}
			switch (node[n].State)
			{

				// ******************** Backoff state *************************
			case 2:

				init[n] = 1;			// Node is on the current backoff
				nodebusy[n] = 1;	// Node busy	

				if (node[n].BackoffPeriod == 0)
				{
					node[n].State = 3;							// Switch to carrier sensing in the next slot

				}
				else
				{
					node[n].State = 2;							// Stay in the backoff state
					node[n].BackoffPeriod--;					// Decrease Backoff 
				}

				break;

				// ******************** Sensing state *************************
			case 3:
				init[n] = 1;	// Node trying to send a packet
				if (node[n].carrier_sensing == 1 && chbusy == 0) // If channel is idle AND doing carrier sensing
				{
					node[n].carrier_sensing--;
					node[n].State = 4;	// Switch to Tx state in the next slot
					chbusy_cnt++;		// make channel busy
				}
				else	// Channel is BUSY
				{
					
					node[n].k++;
					if (node[n].k <= 5) {
						node[n].BackoffPeriod = rand() % (power(2, (node[n].k)));
						//printf("node[n].BackoffPeriod = %d\n",node[n].BackoffPeriod);
						node[n].State = 2;

					}
					else {  //drop data
						nodebusy[n] = 0;
						//init[n]=0;
						node[n].State = 1;


					}
				}

				break;

				// ******************** Tx state *************************
			case 4:
				//trans_attempt++;
				if (tx_cnt[n] == TxCntInit)
				{
					tx_cnt[n]--; // Stay same state in the next slot

				}
				else if (tx_cnt[n] == 1)
				{
					//trans_attempt++;
					node[n].State = 5;
					chbusy_cnt--;
					//printf("case 4 chbusy_cnt== %d\n",chbusy_cnt);
					//printf("case 4 failure == %d\n",tx_failure);

				}
				else
				{
					tx_cnt[n]--; // Stay same state in the next slot
					//total_pkt++;
				}

				break;

				// ******************** Rx state *************************
			case 5:
				if (chbusy == 0)
				{
					chbusy_cnt++;	// Make CHANNEL BUSY for ACK transmission in the next slot
				}
				else
				{
					//------------------------ WRITE SOME CODE HERE-----------------------------

					if (chbusy == 1)
					{
						//total_pkt++;
						if (rx_cnt[n] == RxCntInit)
						{
							rx_cnt[n]--;        // Stay same state in the next slot
							//total_suc++;
						}
						else if (rx_cnt[n] == 1)  //Rx sucuess
						{
							//printf("trans suc\n");
							chbusy_cnt--;
							init[n] = 0;
							total_suc++;
							trans_attempt++;



						}
						else
						{
							rx_cnt[n]--;
						}
					}
					else
					{
						node[n].State = 6;
					}
				}
				break;

				// ******************** Time OUT state *************************
			case 6:

				if (node[n].TimeOut == 1)
				{
					tx_failure++;
					trans_attempt++;
					// reset
					init[n] = 0;
					chbusy_cnt--;
					//node[n].TimeOut=3;

				}
				else
				{
					node[n].TimeOut--;
					node[n].State = 5;
				}
				break;
			} // END: (( switch (node[n].State) ))
		//chbusy = chbusy_cnt;
		} // END: Node loop

		chbusy = chbusy_cnt;
		//printf("chbusy : %d\n",chbusy);
	}// END: simulation time

	//****************** Output **************************
	printf("node : %d \n", NumNode);
	printf("Tx_failure: %d\n", tx_failure);
	printf("TOTAL Trans_attempt:%d\n", trans_attempt);
	printf("TOTAL Success:%d\n", total_suc);
	printf("network tx_failure/attempt: %f\n", (double)tx_failure / trans_attempt);
}
