#include <stdio.h>

/* Methodology:
 *
 *	Let P(i) be the probability of the i-th person wins at a start of a round.
 *
 *	P(i) = (probability that (i - 1) people before this person do not win) *
 *	       (probability that this person wins at his turn + probability that this
 *		person does not win at his turn, but win in the future)
 *
 *	probability that (i - 1) people before this person do not win) = (1 - p)^(i - 1)
 *
 * 	probability that this person wins at his turn = p
 *
 *	probability that this person does not win at his turn, but win in the future =
 *		(1 - p) * (probability that N - i - 1 people after him does not win)
 *			* (probability of the i-th person wins at a start of a round)
 *		= (1 - p) * (1 - p)^(N - i) * P(i)
 *		= (1 - p)^(N - i + 1) * P(i)
 *
 *	P(i) = (1 - p)^(i - 1) (p + (1 - p)^(N - i + 1) * P(i)
 *	     = p(1 - p)^(i - 1) + (1 - p)^N * P(i)
 *	
 * So   P(i) = p(1 - p)^(i - 1) / [1 - (1 - p)^N]
 *
 * Corner case:
 *	+ When p = 0, P(i) = 0
 *	+ When p = 1, P(1) = 1, P(i) = 0 for all i != 0
 */
int main(void)
{
	return 0;
}
