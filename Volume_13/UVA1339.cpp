/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Let A be the array of size 26, which is the sorted array of alphabet character
 *          frequencies of the original string S.
 *  + KEY OBSERVATION: The encryption methods, substitution cipher and permutation cipher,
 *          preserve the array A.
 *  + Therefore, we have the following algorithm to solve this problem:
 *      - Let A, B be the sorted array of alphabet character frequencies of the guess string,
 *          and the decrypt string respectively.
 *      - A and B are of size 26.
 *      - If A and B are the same, the guess is valid. Otherwise, the guess is invalid.
 *
 *  + Time complexity: O(L) where L is the length of the input strings
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const char MAX_LEN = 100;
const char NUM_ALPHA = 26;

int isValidGuess(char decrypt[], char guess[]);

int main(void)
{
    char decrypt[MAX_LEN], guess[MAX_LEN];

    while(scanf("%s %s", decrypt, guess) > 0)
    {
        if(isValidGuess(decrypt, guess))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

// Assumption: The two input strings have equal length */
int isValidGuess(char decrypt[], char guess[])
{
    int charFreqD[NUM_ALPHA] = {0}, charFreqG[NUM_ALPHA] = {0};

    for(int i = 0; decrypt[i] != '\0'; i++)
    {
        charFreqD[decrypt[i] - 'A']++;
        charFreqG[guess[i] - 'A']++;
    }

    sort(charFreqD, charFreqD + NUM_ALPHA);
    sort(charFreqG, charFreqG + NUM_ALPHA);

    for(int i = 0; i < NUM_ALPHA; i++)
        if(charFreqD[i] != charFreqG[i])
            return 0;

    return 1;
}
