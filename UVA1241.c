#include <stdio.h>

#define MAX_SIZE (1 << 10)
#define PRESENT 0
#define ABSENT 1

int getNumWalkoverMatch(int level, int quitPlayer[], int numQuit);

int main(void)
{
    int T, level, quitPlayer[MAX_SIZE], numQuit, i;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d", &level, &numQuit);
        for(i = 0; i < numQuit; i++)
        {
            scanf("%d", &quitPlayer[i]);
            quitPlayer[i]--;
        }

        printf("%d\n", getNumWalkoverMatch(level, quitPlayer, numQuit));
        T--;
    }
    return 0;
}

int getNumWalkoverMatch(int level, int quitPlayer[], int numQuit)
{
    /* Note that PRESENT = 0 */
    int numPlayer = 1 << level, i, playerStatus[MAX_SIZE] = {PRESENT}, numWalkover = 0;

    for(i = 0; i < numQuit; i++)
        playerStatus[quitPlayer[i]] = ABSENT;

    while(numPlayer > 1)
    {
        for(i = 0; i < numPlayer; i += 2)
        {
            if(playerStatus[i] != playerStatus[i + 1])
            {
                numWalkover++;
                playerStatus[i >> 1] = PRESENT;
            }
            else
            {
                if(playerStatus[i] == ABSENT)
                    /* Both are absent */
                    playerStatus[i >> 1] = ABSENT;
                else
                    playerStatus[i >> 1] = PRESENT;
            }
        }

        numPlayer >>= 1;
    }

    return numWalkover;
}
