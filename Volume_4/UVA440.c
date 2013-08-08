/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Because the first city is always cut off first. And Ulm has id = 2.
 *  + If we cut off electricity at every m-th city when counting from 1, then this becomes
 *      a Josephus prolem with n - 1 people, and the count variable is m, and we want
 *      the first person survives.
 *
 *  + Use brute force approach. Increment the value of m starting from 1 until the survivor
 *      of the Josephus problem (n - 1, m) is 1.
 *
 *  + Formula to determine the survivor of the Josephus problem (n, k) (people are numbered from 1):
 *      f(n , k) = ( f(n - 1, k) + k - 1 ) mod n + 1
 *  + Base case: f(1, k) = 1
 */

#include <stdio.h>

const int ULM_ID = 2;

int getJosephusSurvivor(int n, int k);

int main(void)
{
    int numCity, m;

    while(1)
    {
        scanf("%d", &numCity);
        if(!numCity)
            break;

        m = 1;
        while(getJosephusSurvivor(numCity - 1, m) != (ULM_ID - 1))
            m++;

        printf("%d\n", m);
    }
    return 0;
}

int getJosephusSurvivor(int n, int k)
{
    /* When n = 1, the survisor is 1 */
    int result = 1, counter;

    for(counter = 2; counter <= n; counter++)
    {
        result = (result + k - 1) % counter + 1;
    }

    return result;
}
