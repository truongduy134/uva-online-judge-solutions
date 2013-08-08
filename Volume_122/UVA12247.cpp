#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_CARD 3
#define HIGHEST_CARD 52

int main()
{
    int princessCards[MAX_CARD], princeCards[MAX_CARD], index;
    bool allZero;

    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    while(1)
    {
        int isPresent[HIGHEST_CARD + 1] = {0};
        allZero = true;
        for(index = 0; index < MAX_CARD; index++) {
            scanf("%d", &princessCards[index]);
            isPresent[princessCards[index]] = 1;
            if(princessCards[index])
                allZero = false;
        }

        for(index = 0; index < MAX_CARD - 1; index++) {
            scanf("%d", &princeCards[index]);
            isPresent[princeCards[index]] = 1;
            if(princeCards[index])
                allZero = false;
        }

        if(allZero)
            break;

        sort(princessCards, princessCards + MAX_CARD);

        int numPrinceWin, keyCard, minWinKeyCard = 1;
        for(index = 1; index <= HIGHEST_CARD; index++)
            if(!isPresent[index]) {
                minWinKeyCard = index;
                break;
            }
        do
        {
            numPrinceWin = 0;
            for(index = 0; index < MAX_CARD - 1; index++)
                if(princeCards[index] > princessCards[index])
                    numPrinceWin++;
            if(numPrinceWin == 0) {
                // There exists a situation the princess can win the first 2 rounds
                minWinKeyCard = -1;
                break;
            }

            if(numPrinceWin == 1) {
                keyCard = princessCards[MAX_CARD - 1] + 1;
                while(isPresent[keyCard] && keyCard <= HIGHEST_CARD)
                    keyCard++;
                if(keyCard > HIGHEST_CARD)
                {
                    minWinKeyCard = -1;
                    break;
                }
                if(keyCard > minWinKeyCard)
                    minWinKeyCard = keyCard;
            }
        } while(next_permutation(princessCards, princessCards + MAX_CARD));

        printf("%d\n", minWinKeyCard);
    }

    return 0;
}
