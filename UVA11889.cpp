#include <cstdio>
#include <vector>

using namespace std;

const int UPPERBOUND = 3163;

int findSolution(int A, int C, const vector<int> & primeList);
void generatePrimeList(vector<int> & primeList, int upperBound);

int main(void)
{
    vector<int> primeList;

    generatePrimeList(primeList, UPPERBOUND);

    int T, A, C, B;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &A, &C);

        B = findSolution(A, C, primeList);

        if(B < 0)
            printf("NO SOLUTION\n");
        else
            printf("%d\n", B);

        T--;
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

            for(int multipleN = n + n; multipleN <= upperBound; multipleN += n)
                primeSieve[multipleN] = false;
        }
}

/* findSolution(...): returns the smallest B such that lcm(A, B) = C. If B does not
 *      exist, return -1.
 *
 * Methodology:
 *  + If C is not divisible by A, return -1.
 *  + Otherwise, use the following theorem to derive B:
 *          Let the prime factorization of A and B be
 *              A = p1^a1 * p2*a2 * ... * p(n)^a(n)
 *              B = p1^b1 * p2*b2 * ... * p(n)^b(n)
 *          Then
 *              C = p1^(max(a1, b1)) * ... * p(n)^(max(a(n), b(n)))
 */
int findSolution(int A, int C, const vector<int> & primeList)
{
    if(C % A != 0)
        return -1;
    if(C == A)
        return 1;

    int B = 1, cpyA = A, powerA, powerC;

    for(int ind = 0; ind < (int) primeList.size(); ind++)
    {
        if(primeList[ind] * primeList[ind] > cpyA)
            break;

        powerA = 1;
        powerC = 1;
        while(A % primeList[ind] == 0)
        {
            powerA *= primeList[ind];
            A /= primeList[ind];
        }
        while(C % primeList[ind] == 0)
        {
            powerC *= primeList[ind];
            C /= primeList[ind];
        }

        if(powerC > 1 && powerA < powerC)
            B *= powerC;
    }

    if(A > 1)
    {
        // A is the last prime factor of C
        powerA = A;
        powerC = 1;
        while(C % A == 0)
        {
            powerC *= A;
            C /= A;
        }

        if(powerC > 1 && powerA < powerC)
            B *= powerC;
    }

    if(C > 1)
        B *= C;

    return B;

}
