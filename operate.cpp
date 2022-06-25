#include "operate.h"

int power(int i, int j)
{
	int temp;

	if (j == 0)
		temp = 1;
	else if (j == 1)
		temp = i;
	else if (j == 2)
		temp = i * i;
	else
		temp = i * power(i, (j - 1));

	return temp;
}

double power(double i, int j)
{
	double temp;
	if (j == 0)
		temp = 1;
	else if (j == 1)
		temp = i;
	else if (j == 2)
		temp = i * i;
	else
		temp = i * power(i, (j - 1));

	return temp;
}
//*/


int min(int i, int j)
{
	if (i < j)
		return i;
	else
		return j;
}

int max(int i, int j)
{
	if (i >= j)
		return i;
	else
		return j;
}