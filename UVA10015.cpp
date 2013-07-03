/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This is a variant of Josephus' Problem.
 *  + Generate the first 3501 primes (Note that in each round, we use 1 prime and can delete 1 person.
 *            Since there are totally 3501 people, we need 3501 primes )
 *  + After that, simulate the process in a brute-force manner.
 *    In this problem, it is better to use circular array instead of linked list to do the simulation because
 *          the number of counting step is much larger than the size of the circle.
 *
 *  + Time complexity: O(n^2) (n is the number of people initially)
 */

#include <cstdio>
#include <vector>
#include <iterator>

using namespace std;

const int UPPER_BOUND = 33000;
const int MAX_NUM_PEOPLE = 3501;

void generatePrimeList(vector<int> & primeList, int upperBound);
int getJosephusSurvivor(int numPeople, const vector<int> & primeList);

int main(void)
{
    vector<int> primeList;
    int numPeople;
    vector<int> memoTable(MAX_NUM_PEOPLE + 1, -1);

    generatePrimeList(primeList, UPPER_BOUND);

    memoTable[0] = 0;

    while(1)
    {
        scanf("%d", &numPeople);
        if(!numPeople)
            break;

        if(memoTable[numPeople] < 0)
            memoTable[numPeople] = getJosephusSurvivor(numPeople, primeList);
        printf("%d\n", memoTable[numPeople]);
    }
    return 0;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
    primeList.clear();

    vector<bool> primeSieve(upperBound, true);

    for(int n = 2; n < upperBound; n++)
        if(primeSieve[n])
        {
            primeList.push_back(n);

            for(int nextN = n + n; nextN < upperBound; nextN += n)
                primeSieve[nextN] = false;
        }
}

int getJosephusSurvivor(int numPeople, const vector<int> & primeList)
{
    vector<int> circle(numPeople, 0);

    for(int n = 1; n <= numPeople; n++)
        circle[n - 1] = n;

    int primeInd = 0, curInd = 0, sizeCircle = numPeople;

    while(sizeCircle > 1)
    {
        int deleteInd = (curInd + primeList[primeInd] - 1) % sizeCircle;

        circle.erase(circle.begin() + deleteInd);
        sizeCircle--;

        curInd = deleteInd;
        if(curInd == sizeCircle)
            curInd = 0;

        primeInd++;
    }

    return circle[0];
}
