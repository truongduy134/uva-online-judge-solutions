/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + We can have an O(n) solution by doing the simulation with stack.
 *
 *  + Consider the initial arrangement A, the desired arragement B,
 *      and the stack S (representing the station).
 *  + If the current element in B = current element in A
 *      - Move that element to the station, then continue to move it to B immediately.
 *      - Consider the next element in both A and B.
 *    Otherwise,
 *      - We consider the top element of S (if exists).
 *      - If the top of S = the current element in B, we move it to B by popping the stack.
 *      - Consider the next element in B.
 *    Otherwise,
 *      - We have to push something from A to the stack and consider the next element of A.
 *      - If there is no more element in A, then the rearrangment is impossible.
 *  + Continue to do this until we realize the rearrangment is impossible or there is no
 &      more element in B to consider (which means the answer is YES)
 */

#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

bool doRailSimulation(int numBlock, const vector<int> & desiredPermu);

int main(void)
{
    int numBlock, blockId;
    vector<int> desiredPermu;

    while(1)
    {
        scanf("%d", &numBlock);
        if(!numBlock)
            break;

        desiredPermu.assign(numBlock, 0);
        while(1)
        {
            scanf("%d", &blockId);
            if(!blockId)
                break;

            desiredPermu[0] = blockId;
            for(int i = 1; i < numBlock; i++)
                scanf("%d", &desiredPermu[i]);

            if(doRailSimulation(numBlock, desiredPermu))
                printf("Yes\n");
            else
                printf("No\n");
        }
        printf("\n");
    }
    return 0;
}

bool doRailSimulation(int numBlock, const vector<int> & desiredPermu)
{
    vector<int> init(numBlock, 0);
    stack<int> station;

    for(int i = 1; i <= numBlock; i++)
        init[i - 1] = i;

    int initInd = 0, resultInd = 0;

    while(resultInd < numBlock)
    {
        if(initInd < numBlock && desiredPermu[resultInd] == init[initInd])
        {
            // Move this block from A to station, then to B immediately
            resultInd++;
            initInd++;
        }
        else
        {
            // Check the top of the stack station
            if(station.empty() == false && desiredPermu[resultInd] == station.top())
            {
                // Move the block from station to B
                station.pop();
                resultInd++;
            }
            else
            {
                // Push the block in A to station (if possible)
                if(initInd < numBlock)
                {
                    station.push(init[initInd]);
                    initInd++;
                }
                else
                    return false;
            }
        }
    }

    return true;
}
