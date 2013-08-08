#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define MAX_LEN 21
#define MAX_PATCH 102
#define INFINITY 1000000000

struct patch_s {
    int time, bugPresentRequired, bugAbsentRequired, bugProduced, bugEliminated;
};

typedef struct patch_s patch_t;

int  findTimeToRemoveAllBugs(patch_t patchArr[], int numPatch, int numBug)
{
    vector<int> minDist(1 << numBug);
    for(int i = 0; i < (int) minDist.size(); i++)
        minDist[i] = INFINITY;

    int initState = (1 << numBug) - 1;

    minDist[initState] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pqState;
    pqState.push(make_pair(0, initState));

    while(!pqState.empty())
    {
        pair<int, int> curState = pqState.top();
        pqState.pop();

        int time = curState.first;
        int stateStr = curState.second;

        if(time == minDist[stateStr])
        {
            for(int i = 0; i < numPatch; i++) {
                if((stateStr & patchArr[i].bugPresentRequired) ==  patchArr[i].bugPresentRequired &&
                   (~stateStr & patchArr[i].bugAbsentRequired) == patchArr[i].bugAbsentRequired)
                {
                    int newStateStr = stateStr | patchArr[i].bugProduced;
                    newStateStr &= ~ patchArr[i].bugEliminated;

                    if(time + patchArr[i].time < minDist[newStateStr])
                    {
                        minDist[newStateStr] = time + patchArr[i].time;
                        pqState.push(make_pair(time + patchArr[i].time, newStateStr));
                    }
                }
            }
        }
    }

    int destState = 0;

    if(minDist[destState] >= INFINITY)
        return -1;
    return minDist[destState];
}

int main(void)
{
    int numBug, numPatch, productNo, time;
    patch_t patchArr[MAX_PATCH];
    char bugRequired[MAX_LEN], bugProduced[MAX_LEN];
 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    productNo = 0;
    while(1)
    {
        scanf("%d %d", &numBug, &numPatch);
        if(numBug == 0 && numPatch == 0)
            break;

        productNo++;
        for(int i = 0; i < numPatch; i++)
        {
            scanf("%d %s %s", &patchArr[i].time, bugRequired, bugProduced);
            patchArr[i].bugAbsentRequired = 0;
            patchArr[i].bugEliminated = 0;
            patchArr[i].bugProduced = 0;
            patchArr[i].bugPresentRequired = 0;

            for(int j = 0; bugRequired[j] != '\0'; j++)
                if(bugRequired[j] == '+')
                    patchArr[i].bugPresentRequired |= (1 << j);
                else
                    if(bugRequired[j] == '-')
                        patchArr[i].bugAbsentRequired |= (1 << j);

            for(int j = 0; bugProduced[j] != '\0'; j++)
                if(bugProduced[j] == '+')
                    patchArr[i].bugProduced |= (1 << j);
                else
                    if(bugProduced[j] == '-')
                        patchArr[i].bugEliminated |= (1 << j);
        }

        time = findTimeToRemoveAllBugs(patchArr, numPatch, numBug);

        printf("Product %d\n", productNo);
        if(time < 0)
            printf("Bugs cannot be fixed.\n");
        else
            printf("Fastest sequence takes %d seconds.\n", time);
        printf("\n");
    }
    return 0;
}
