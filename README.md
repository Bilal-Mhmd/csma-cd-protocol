# csma-cd-protocol
a C/C++ code to implement the CSMA/CD algorithm
the program output should demonstrate the contention of 10 stations to gain access on a shared bus using (1-persistent algorithm with binary exponential backoff) as follows:
Step1: If the medium is idle, transmit; otherwise, go to step 2
Step2: If the medium is busy, continue to listen until the channel is idle, then transmit immediately
Step3: If a collision is detected, transmit a brief jamming signal to assure that all stations know that there has been a collision and cease transmission
Step4: After transmitting the jamming signal, wait a random amount of time, referred to as the backoff, then attempt to transmit again
