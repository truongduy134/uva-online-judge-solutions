#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int UPPERBOUND = 2000000;

bool compareByNumPrimeFactor(const pair<int, int> & one, const pair<int, int> & two);
void prepareNumPrimeFactorSieve(vector<pair<int, int> > & numPrimeFactorSieve, int upperBound);

int main(void)
{
    vector<pair<int, int> > numPrimeFactorSieve;

    prepareNumPrimeFactorSieve(numPrimeFactorSieve, UPPERBOUND);

    sort(numPrimeFactorSieve.begin(), numPrimeFactorSieve.end(), compareByNumPrimeFactor);

    int id, caseId;
    caseId = 1;
    while(1)
    {
        scanf("%d", &id);
        if(!id)
            break;

        printf("Case %d: %d\n", caseId, numPrimeFactorSieve[id].first);

        caseId++;
    }
    return 0;
}

bool compareByNumPrimeFactor(const pair<int, int> & one, const pair<int, int> & two)
{
    if(one.second < two.second)
        return true;
    if(one.second > two.second)
        return false;
    return one.first < two.first;
}
void prepareNumPrimeFactorSieve(vector<pair<int, int> > & numPrimeFactorSieve, int upperBound)
{
    numPrimeFactorSieve.assign(upperBound + 1, pair<int, int> (0, 0));

    for(int i = 0; i <= upperBound; i++)
        numPrimeFactorSieve[i].first = i;

    for(int n = 2; n <= upperBound; n++)
        if(numPrimeFactorSieve[n].second == 0)
        {
            // n is a prime.
            int powerN = n;
            while(powerN <= upperBound)
            {
                for(int multipleN = powerN; multipleN <= upperBound; multipleN += powerN)
                    numPrimeFactorSieve[multipleN].second++;

                if(powerN <= upperBound / n)
                    powerN *= n;
                else
                    break;
            }
        }
}
