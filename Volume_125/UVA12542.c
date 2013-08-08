#include <stdio.h>
#include <string.h>

#define MAX_PRIME_VAL 100000
#define MAX_LEN 300

int findMaxPrimeSubstr(char strNum[], int primeSieve[]);
void preparePrimeSieve(int primeSieve[], int maxVal);

int main(void)
{
    int primeSieve[MAX_PRIME_VAL + 1];
    char strNum[MAX_LEN + 1];

    preparePrimeSieve(primeSieve, MAX_PRIME_VAL);

    while(1)
    {
        gets(strNum);
        if(strNum[0] == '0' && strNum[1] == '\0')
            break;

        printf("%d\n", findMaxPrimeSubstr(strNum, primeSieve));
    }

    return 0;
}

void preparePrimeSieve(int primeSieve[], int maxVal)
{
    int n, multipleN;

    memset(primeSieve, 1, (maxVal + 1) * sizeof(int));

    primeSieve[0] = 0;
    primeSieve[1] = 0;

    for(n = 2; n <= maxVal; n++)
        if(primeSieve[n])
        {
            /* Multiple of n is not a prime */
            multipleN = n + n;
            while(multipleN <= maxVal)
            {
                primeSieve[multipleN] = 0;
                multipleN += n;
            }
        }
}

int findMaxPrimeSubstr(char strNum[], int primeSieve[])
{
    int leftInd, rightInd, numVal, maxPrimeVal = 0;

    for(leftInd = 0; strNum[leftInd] != '\0'; leftInd++)
    {
        numVal = 0;
        for(rightInd = leftInd; strNum[rightInd] != '\0'; rightInd++)
        {
            numVal = numVal * 10 + (strNum[rightInd] - '0');
            if(numVal > MAX_PRIME_VAL)
                break;

            if(primeSieve[numVal] && numVal > maxPrimeVal)
                maxPrimeVal = numVal;
        }
    }

    return maxPrimeVal;

}
