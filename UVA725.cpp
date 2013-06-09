/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + This problem can be solved using a brute force approach
 *
 *  + Problem description:
 *      - Given N <= 79, find two 5-digit numbers A and B
 *        (that can have leading zeroea) such that
 *              A / B = N and
 *              The string AB is a permutation of 0, 1, 2, ..., 9
 *
 *  + First, we generate a list L of all numbers 1000 <= B < 10^6 such that
 *              all digits of B are distinct
 *
 *  + Hence, consider each number B in L
 *       - Check if the array of digits of B and N * B is a permutation of 0, 1, ..., 9
 *       - If so, A = N * B
 */

#include <cstdio>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

const int LEN_NUM = 5;
const int NUM_DIGIT = 10;

void findAllPairResult(int N, const vector<int> & sortedDistinctDigitNumList, vector<pair<int, int> >& pairResultList);
void generateSortedDistinctDigitNumList(vector<int> & sortedDistinctDigitNumList);
void generateSortedDistinctDigitNumList(vector<int> & sortedDistinctDigitNumList);
int getPowerTen(int pow);
bool hasDistinctDigits(int N);
bool hasDistinctDigits(int A, int B);

int main(void)
{
    vector<int> sortedDistinctDigitNumList;
    vector<pair<int, int> > pairResultList;

    generateSortedDistinctDigitNumList(sortedDistinctDigitNumList);

    int N;
    bool isFirst = true;

    while(1)
    {
        scanf("%d", &N);
        if(!N)
            break;

        findAllPairResult(N, sortedDistinctDigitNumList, pairResultList);

        if(isFirst)
            isFirst = false;
        else
            printf("\n");

        if(pairResultList.size() == 0)
            printf("There are no solutions for %d.\n", N);
        else
        {
            for(int i = 0; i < (int) pairResultList.size(); i++)
                printf("%05d / %05d = %d\n", pairResultList[i].first, pairResultList[i].second, N);
        }
    }
    return 0;
}

void findAllPairResult(int N, const vector<int> & sortedDistinctDigitNumList, vector<pair<int, int> >& pairResultList)
{
        pairResultList.clear();

        int upperBound = getPowerTen(LEN_NUM);
        for(int i = 0; i < (int) sortedDistinctDigitNumList.size(); i++)
        {
            int B = sortedDistinctDigitNumList[i];
            int A = B * N;

            if(A >= upperBound)
                break;

            if(hasDistinctDigits(A, B))
                pairResultList.push_back(pair<int, int>(A, B));
        }
}

void generateSortedDistinctDigitNumList(vector<int> & sortedDistinctDigitNumList)
{
    sortedDistinctDigitNumList.clear();

    int lowerBound = getPowerTen(LEN_NUM - 2);
    int upperBound = getPowerTen(LEN_NUM);

    for(int n = lowerBound; n < upperBound; n++)
        if(hasDistinctDigits(n))
            sortedDistinctDigitNumList.push_back(n);
}

// Return 10^pow
int getPowerTen(int pow)
{
    int tenPow = 1;

    for(int d = 1; d <= pow; d++)
        tenPow *= 10;
    return tenPow;
}

bool hasDistinctDigits(int N)
{
    int numDigit = 0, digitCount[NUM_DIGIT] = {0};

    while(N)
    {
        digitCount[N % 10]++;
        N /= 10;
        numDigit++;
    }

    while(numDigit < LEN_NUM)
    {
        numDigit++;
        digitCount[0]++;
    }

    for(int d = 0; d < NUM_DIGIT; d++)
        if(digitCount[d] > 1)
            return false;
    return true;
}

// Check if the digit string AB has distinct digits
bool hasDistinctDigits(int A, int B)
{
    int arrNum[2], digitCount[NUM_DIGIT] = {0};

    arrNum[0] = A;
    arrNum[1] = B;

    for(int i = 0; i < 2; i++)
    {
        int N = arrNum[i];
        int numDigit = 0;

        while(N)
        {
            digitCount[N % 10]++;
            N /= 10;
            numDigit++;
        }

        while(numDigit < LEN_NUM)
        {
            numDigit++;
            digitCount[0]++;
        }
    }

    for(int d = 0; d < NUM_DIGIT; d++)
        if(digitCount[d] > 1)
            return false;
    return true;
}
