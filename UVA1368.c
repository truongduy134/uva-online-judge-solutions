/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + We use greedy approach to solve this problem.
 *  + Let CS be the concencus string we want to construct.
 *  + At each position i, we count the number of occurences of type A, C, G, T appeared at position i
 *       among all DNA in the given set. Denote these numbers as A[i], C[i], G[i], T[i].
 *       Then CS[i] = the symbol X such that X[i] is the largest among A[i], C[i], G[i], T[i]
 *       If there are ties, choose X as the smallest alphabet.
 *  + Then the concencus error can be computed as
 *       CE = sum (N - X[i]) for i = 0, 1, ..., L where N is the number of DNA.
 *
 *  + Time complexity: O(N * L) where N is the number of DNA, L is the length of the DNA strings
 */

#include <stdio.h>
#include <string.h>

#define NUM_ALPHA 26
const int MAX_NUM_DNA = 50;
const int MAX_LEN_DNA = 1000;
const char DNA_TYPE[] = "ACGT";
const char NUM_TYPE_DNA = 4;

int findConcencusDna(char dnaList[][MAX_LEN_DNA + 1], int numDna, int lenDna, char concencusDna[]);

int main(void)
{
    char dnaList[MAX_NUM_DNA][MAX_LEN_DNA + 1], concencusDna[MAX_LEN_DNA + 1];
    int T, lenDna, numDna, i, concencusError;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &numDna, &lenDna);

        for(i = 0; i < numDna; i++)
            scanf("%s", dnaList[i]);

        concencusError = findConcencusDna(dnaList, numDna, lenDna, concencusDna);

        printf("%s\n%d\n", concencusDna, concencusError);
        T--;
    }
    return 0;
}

int findConcencusDna(char dnaList[][MAX_LEN_DNA + 1], int numDna, int lenDna, char concencusDna[])
{
    int dnaId, lenId, typeAmount[NUM_ALPHA] = {0}, error, type, maxType;

    error = 0;

    for(lenId = 0; lenId < lenDna; lenId++)
    {
        for(type = 0; DNA_TYPE[type] != '\0'; type++)
            typeAmount[DNA_TYPE[type] - 'A'] = 0;

        for(dnaId = 0; dnaId < numDna; dnaId++)
            typeAmount[dnaList[dnaId][lenId] - 'A']++;

        maxType = 0;
        for(type = 1; type < NUM_TYPE_DNA; type++)
            if(typeAmount[DNA_TYPE[type] - 'A'] > typeAmount[DNA_TYPE[maxType] - 'A'])
                maxType = type;
        concencusDna[lenId] = DNA_TYPE[maxType];
        error += (numDna - typeAmount[DNA_TYPE[maxType] - 'A']);
    }
    concencusDna[lenDna] = '\0';

    return error;
}
