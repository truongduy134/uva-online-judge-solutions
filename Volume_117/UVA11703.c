/********************************************************************************
 * sqrtLogSin.c
 *
 * UVA Problem ID: 11703 (sqrt log sin)
 *
 * Input:
 * 	+ The input consists of many test cases.
 *  + For each test case, there is one integer I. (0 <= I <= 10^6)
 *  + I = -1 terminates the input.
 *
 * Output:
 * 	+ For each test case, print s(i) modulo 10^6 where s(i) is the i-th term
 * 	  of the sequence (s(i)).
 *
 * Definition: The sequence (s(i)) is defined as follows:
 * 		- s(0) = 1.
 * 		- s(i) = s(floor(i - squareRoot(i))) + s(floor(ln(i)))
 * 					+ s(floor(i * [sin(i)]^2)) for i >= 1.
 ********************************************************************************/

#include <stdio.h>
#include <math.h>
#define MODULO 1000000L
#define MAX 1000000L

void computeSequenceTerm(long int []);

int main(void)
{
	long int sequence[MAX + 1], termSerial;

	/* Pre-processing */
	computeSequenceTerm(sequence);

	while(1)
	{
		scanf("%ld", &termSerial);
		if(termSerial < 0)
			break;

		/* Time complexity: O(1) per query */
		printf("%ld\n", sequence[termSerial]);
	}
	return 0;
}

/********************************************************************************
 * The function computeSequenceTerm(S): computes the first (MAX + 1) terms
 * 				in the sequence (s(i)) (i.e. i = 0, 1, ..., MAX) and stores
 * 				them in the array S. Note that all the values will be taken
 * 				modulo with MODULO = 10^6.
 ********************************************************************************/
void computeSequenceTerm(long int sequence[])
{
	long int index;

	sequence[0] = 1;
	for(index = 1; index <= MAX; index++)
		sequence[index] = (sequence[(long int) (index - sqrt(index))] % MODULO
		                + sequence[(long int) (log(index))] % MODULO
		                + sequence[(long int) (index * sin(index) * sin(index))]
		                  % MODULO) % MODULO;
}
