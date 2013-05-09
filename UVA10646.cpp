#include <iostream>
#include <vector>
#include <ctype.h>

using namespace std;

#define NUM_CARD 52
#define TAKE_TOP 25
#define NUM_REMOVE 3

void initCardPtr(vector<int> &cardPtr);
int getCardValue(char valChar);

int main()
{
    string initPile, trash;
    int caseId;
    // cardPtr[i] will 'point' to the i-th card in the pile.
    int numTest;

    cin >> numTest;
    getline(cin, trash);    // Get rid of the new line character

    caseId = 1;
    while(caseId <= numTest)
    {
        // Letters in initPile (from left to right) represents
        // the pile of 52 cards from bottom to top
        getline(cin, initPile);

        vector<int> cardPtr(NUM_CARD);
        initCardPtr(cardPtr);

        /* Simulate the process */
        int finalPos = 0, targetIndex, val;
        targetIndex = NUM_CARD - TAKE_TOP - 1;

        for(int index = 0; index < NUM_REMOVE; index++)
        {

            val = getCardValue(initPile[cardPtr[targetIndex]]);
            finalPos += val;

            /* Remove card */
            cardPtr.erase(cardPtr.begin() + targetIndex - (10 - val), cardPtr.begin() + targetIndex + 1);

            /* Top of the card */
            targetIndex -= (10 - val + 1);
        }

        /* Output */
        cout << "Case " << caseId << ": " << initPile[cardPtr[finalPos - 1]] << initPile[cardPtr[finalPos - 1] + 1] << endl;

        /* Erase the target card and 10 - val card */
        caseId++;
    }
    return 0;
}

void initCardPtr(vector<int> &cardPtr)
{
    cardPtr[0] = 0;
    for(int index = 1; index < NUM_CARD; index++)
        // Each card has 2 characters, plus a separating white space
        cardPtr[index] = cardPtr[index - 1] + 3;
}

int getCardValue(char valChar)
{
    if(isdigit(valChar))
        return valChar - '0';

    return 10;
}
