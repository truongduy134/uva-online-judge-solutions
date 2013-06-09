/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Let L be a list of primes less than 10000. L can be generated using Sieve of Eratosthenes algorithm
 *  + The size of L is about 1300.
 *  + Let f(n) = the number of ways to express n as the sum of consecutive primes.
 *  + Hence, we can have a solution with
 *      - O(|L|^2) straightforwardpre-processing to calculate f(n) for all n <= 10000
 *        Note that in total there are O(|L|^2) segment sums L[i ... j] = L[i] + .... + L[j]
 *      - O(1) querying.
 */

#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 10000;

void generatePrimeList(vector<int> & primeList, int upperBound);
void calculateNumSumConsecutivePrime(vector<int> & numSumConsecutivePrime, const vector<int> & primeList, int upperBound);

int main(void)
{
    vector<int> primeList;
    generatePrimeList(primeList, UPPERBOUND);

    vector<int> numSumConsecutivePrime;
    calculateNumSumConsecutivePrime(numSumConsecutivePrime, primeList, UPPERBOUND);

    int n;
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        printf("%d\n", numSumConsecutivePrime[n]);
    }

    return 0;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
    primeList.clear();
    vector<bool> primeSieve(upperBound + 1, true);

    primeSieve[0] = primeSieve[1] = false;

    for(int n = 2; n <= UPPERBOUND; n++)
        if(primeSieve[n])
        {
            primeList.push_back(n);

            for(int multipleN = n + n; multipleN <= UPPERBOUND; multipleN += n)
                primeSieve[multipleN] = false;
        }
}

void calculateNumSumConsecutivePrime(vector<int> & numSumConsecutivePrime, const vector<int> & primeList, int upperBound)
{
    numSumConsecutivePrime.assign(upperBound + 1, 0);

    for(int left = 0; left < (int) primeList.size(); left++)
    {
        int primeSum = 0;

        for(int right = left; right < (int) primeList.size(); right++)
        {
            primeSum += primeList[right];
            if(primeSum > upperBound)
                break;

            numSumConsecutivePrime[primeSum]++;
        }
    }
}
