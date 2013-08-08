/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Since the input size is small, we can do a straightforward simulation to solve this problem
 */

#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

const int GRANT_AMOUNT = 40;

void doSimulation(int numStudent, int capacity, int grant, vector<int> & leaveOrder);

int main(void)
{
    vector<int> leaveOrder;
    int numStudent, capacity;

    while(1)
    {
        scanf("%d %d", &numStudent, &capacity);
        if(numStudent == 0 && capacity == 0)
            break;

        doSimulation(numStudent, capacity, GRANT_AMOUNT, leaveOrder);

        for(int i = 0; i < numStudent; i++)
            printf("%3d", leaveOrder[i]);
        printf("\n");
    }
    return 0;
}

void doSimulation(int numStudent, int capacity, int grant, vector<int> & leaveOrder)
{
    leaveOrder.clear();
    queue<pair<int, int> > mQueue;

    for(int i = 1; i <= numStudent; i++)
        mQueue.push(pair<int, int>(i, grant));

    int amount = 0, payAmount, rechargeAmount = 1;
    pair<int, int> curStudent;

    while(!mQueue.empty())
    {
        if(amount == 0)
        {
            // Recharge
            amount = rechargeAmount;
            rechargeAmount++;
            if(rechargeAmount > capacity)
                rechargeAmount = 1;
        }

        curStudent = mQueue.front();
        mQueue.pop();

        if(curStudent.second >= amount)
            payAmount = amount;
        else
            payAmount = curStudent.second;

        curStudent.second -= payAmount;

        if(curStudent.second == 0)
            // Leave queue
            leaveOrder.push_back(curStudent.first);
        else
            mQueue.push(curStudent);

        amount -= payAmount;
    }
}
