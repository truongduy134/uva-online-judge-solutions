#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

int findSizeIntersection(const vector<int> & setOne, const vector<int> & setTwo);
void selectDistinctElements(const vector<int> & multiSet, vector<int> & distinctSet);
int findMaximumCardExchange(const vector<int> & aliceCards, const vector<int> & bettyCards);

int main(void)
{
    int numAliceCard, numBettyCard;
    vector<int> aliceCards, bettyCards;

    while(1)
    {
        scanf("%d %d", &numAliceCard, &numBettyCard);
        if(numAliceCard == 0 && numBettyCard == 0)
            break;

        aliceCards.assign(numAliceCard, 0);
        bettyCards.assign(numBettyCard, 0);

        for(int i = 0; i < numAliceCard; i++)
            scanf("%d", &aliceCards[i]);
        for(int i = 0; i < numBettyCard; i++)
            scanf("%d", &bettyCards[i]);

        printf("%d\n", findMaximumCardExchange(aliceCards, bettyCards));
    }
    return 0;
}

int findMaximumCardExchange(const vector<int> & aliceCards, const vector<int> & bettyCards)
{
    vector<int> distinctAliceCards, distinctBettyCards;

    selectDistinctElements(aliceCards, distinctAliceCards);
    selectDistinctElements(bettyCards, distinctBettyCards);

    int numCommon = findSizeIntersection(distinctAliceCards, distinctBettyCards);
    int numDistinctAliceOnly = distinctAliceCards.size() - numCommon;
    int numDistinctBettyOnly = distinctBettyCards.size() - numCommon;

    if(numDistinctAliceOnly < numDistinctBettyOnly)
        return numDistinctAliceOnly;
    return numDistinctBettyOnly;
}

// Assumption: multiSet is sorted in non-descending order
void selectDistinctElements(const vector<int> & multiSet, vector<int> & distinctSet)
{
    distinctSet.clear();

    if(multiSet.empty())
        return;

    int prev = multiSet[0];
    distinctSet.push_back(prev);

    for(int i = 1; i < (int) multiSet.size(); i++)
        if(multiSet[i] != prev)
        {
            prev = multiSet[i];
            distinctSet.push_back(prev);
        }
}

// Assumption:
//     + Elements in setOne, setTwo are distinct
//     + Elements in setOne, setTwo are ordered in non-descending order.
int findSizeIntersection(const vector<int> & setOne, const vector<int> & setTwo)
{
    int sizeOne = (int) setOne.size(), sizeTwo = (int) setTwo.size(), indOne, indTwo, numCommon;

    indOne = indTwo = numCommon = 0;

    while(indOne < sizeOne && indTwo < sizeTwo)
    {
        if(setOne[indOne] == setTwo[indTwo])
        {
            indOne++;
            indTwo++;
            numCommon++;
        }
        else
        {
            if(setOne[indOne] < setTwo[indTwo])
                indOne++;
            else
                indTwo++;
        }
    }

    return numCommon;
}
