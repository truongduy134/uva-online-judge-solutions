#include <cstdio>
#include <vector>

using namespace std;

#define UPPERBOUND 10000

void generatePrimeList(vector<int> & primeList, int upperBound);
int getSmallestPrimeDivisor(int n, const vector<int> & primeList);

int main(void)
{
    int caseId, T, n, A, B, C, D;
    vector<int> primeList;

    generatePrimeList(primeList, UPPERBOUND);

    scanf("%d", &T);
    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d", &n);

        // Task: find 4 distinct A, B, C, D such that
        //          n = A * B * C * D and A, B, C, D > 1
        // Assumption: n is given such that A, B, C, D always exists
        A = getSmallestPrimeDivisor(n, primeList);
        B = n / A;
        C = A * getSmallestPrimeDivisor(B, primeList);
        D = n / C;

        printf("Case #%d: %d = %d * %d = %d * %d\n", caseId, n, A, B, C, D);

        caseId++;
    }
    return 0;
}

void generatePrimeList(vector<int> & primeList, int upperBound)
{
    primeList.clear();

    vector<bool> primeSieve(upperBound + 1, true);

    for(int n = 2; n <= upperBound; n++)
        if(primeSieve[n])
        {
            primeList.push_back(n);

            for(int nextN = n + n; nextN <= upperBound; nextN += n)
                primeSieve[nextN] = false;
        }
}

// Assumption: primeList contains all primes less than or equal to sqrt(n)
int getSmallestPrimeDivisor(int n, const vector<int> & primeList)
{
    for(int ind = 0; ind < (int) primeList.size(); ind++)
        if(n % primeList[ind] == 0)
            return primeList[ind];

    return n;
}
