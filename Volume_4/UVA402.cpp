/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Since the input size is small (there are 50 people and 20 cards (20 iterations)), we
 *      can do a brute-force simulation with C++ STL <list>
 *  + Time complexity: O(N * C) where N is the number of people, C is the number of cards.
 */

#include <cstdio>
#include <list>

using namespace std;

const int NUM_CARDS = 20;

void doSelectionSimulation(int numPeople, int numLucky, int cardsArr[NUM_CARDS], list<int> & luckyPos);

int main(void)
{
    int numPeople, numLucky, cardsArr[NUM_CARDS], caseId;
    list<int> luckyPos;

    caseId = 1;
    while(scanf("%d %d", &numPeople, &numLucky) > 0)
    {
        for(int i = 0; i < NUM_CARDS; i++)
            scanf("%d", &cardsArr[i]);

        doSelectionSimulation(numPeople, numLucky, cardsArr, luckyPos);

        printf("Selection #%d\n", caseId);
        bool isFirst = true;
        for(list<int>::iterator it = luckyPos.begin(); it != luckyPos.end(); it++)
        {
            if(isFirst)
                isFirst = false;
            else
                printf(" ");
            printf("%d", *it);
        }
        printf("\n\n");

        caseId++;
    }

    return 0;
}

void doSelectionSimulation(int numPeople, int numLucky, int cardsArr[NUM_CARDS], list<int> & luckyPos)
{
    luckyPos.clear();
    for(int i = 1; i <= numPeople; i++)
        luckyPos.push_back(i);

    int cardId = 0, numStep;
    bool removeFlg;
    list<int>::iterator it = luckyPos.begin();
    while(cardId < NUM_CARDS && (int) luckyPos.size() > numLucky)
    {
        numStep = cardsArr[cardId];
        removeFlg = true;

        // Count 'numStep' people, starting at the current person
        for(int step = 1; step < numStep; step++)
        {
            it++;
            if(it == luckyPos.end())
            {
                // Reach the end of the list. Do not remove anyone. Take the next cards.
                // Restart counting at the beginning
                removeFlg = false;
                it = luckyPos.begin();
                cardId++;
                break;
            }
        }

        if(removeFlg)
        {
            it = luckyPos.erase(it);
        }

        // Gotcha: What if after deletion, we reach the end of the list?
        // Restart counting at the beginning of the list with the next card
        if(it == luckyPos.end())
        {
             it = luckyPos.begin();
            cardId++;
        }
    }
}
