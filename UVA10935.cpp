#include <cstdio>
#include <deque>
#include <vector>

using namespace std;

void doSimulating(deque<int> & cardDeck, vector<int> & discardCards);

int main(void)
{
    deque<int> cardDeck;
    vector<int> discardCards;
    int numCard;

    while(1)
    {
        scanf("%d", &numCard);
        if(numCard == 0)
            break;

        cardDeck.assign(numCard, 0);
        for(int i = 0; i < numCard; i++)
            cardDeck[i] = i + 1;
        discardCards.clear();

        doSimulating(cardDeck, discardCards);

        printf("Discarded cards:");
        if(discardCards.size() > 0)
        {
            printf(" %d", discardCards[0]);
            for(int i = 1; i < (int) discardCards.size(); i++)
                printf(", %d", discardCards[i]);
        }
        printf("\nRemaining card: %d\n", cardDeck.front());
    }

    return 0;
}
/* Process:
 *      + While there are at least 2 cards in the deck:
 *          - Throw away (discard) the top card
 *          - Move that card that is now on top of the deck to the bottom.
 */
void doSimulating(deque<int> & cardDeck, vector<int> & discardCards)
{
    int topCard;
    while(cardDeck.size() > 1)
    {
        topCard = cardDeck.front();
        cardDeck.pop_front();

        discardCards.push_back(topCard);

        topCard = cardDeck.front();
        cardDeck.pop_front();
        cardDeck.push_back(topCard);
    }
}
