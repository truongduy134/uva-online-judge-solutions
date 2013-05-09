#include <cstdio>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

void clearStack(stack<int> & mStack)
{
    stack<int> mEmpty;
    swap(mEmpty, mStack);
}

void clearQueue(queue<int> & mQueue)
{
    queue<int> mEmpty;
    swap(mEmpty, mQueue);
}

void clearPQueue(priority_queue<int> & mPQueue)
{
    priority_queue<int> mEmpty;
    swap(mEmpty, mPQueue);
}

int main(void)
{
    bool mayStack, mayQueue, mayPQ;
    stack<int> mStack;
    queue<int> mQueue;
    priority_queue<int> mPQueue;

    int numOp, opType, val, popVal, numCorrect;

//    freopen("in.txt", "r", stdin);

    while(scanf("%d", &numOp) > 0)
    {
        // Clear
        clearStack(mStack);
        clearQueue(mQueue);
        clearPQueue(mPQueue);
        mayStack = mayQueue = mayPQ = true;

        for(int i = 0; i < numOp; i++)
        {
            scanf("%d %d", &opType, &val);

            if(opType == 1)
            {
                if(mayStack)
                    mStack.push(val);
                if(mayQueue)
                    mQueue.push(val);
                if(mayPQ)
                    mPQueue.push(val);
            }
            else
            {
                // Pop stack
                if(mayStack)
                {
                    if(mStack.empty())
                        mayStack = false;
                    else
                    {
                        popVal = mStack.top();
                        mStack.pop();
                        if(popVal != val)
                            mayStack = false;
                    }
                }

                // Pop queue
                if(mayQueue)
                {
                    if(mQueue.empty())
                        mayQueue = false;
                    else
                    {
                        popVal = mQueue.front();
                        mQueue.pop();
                        if(popVal != val)
                            mayQueue = false;
                    }
                }

                // Pop PQ
                if(mayPQ)
                {
                    if(mPQueue.empty())
                        mayPQ = false;
                    else
                    {
                        popVal = mPQueue.top();
                        mPQueue.pop();
                        if(popVal != val)
                            mayPQ = false;
                    }
                }
            }
        }

        numCorrect = 0;
        if(mayStack)
            numCorrect++;
        if(mayQueue)
            numCorrect++;
        if(mayPQ)
            numCorrect++;
        if(numCorrect == 0)
            printf("impossible\n");
        else
        {
            if(numCorrect > 1)
                printf("not sure\n");
            else
            {
                if(mayStack)
                    printf("stack\n");
                else
                {
                    if(mayQueue)
                        printf("queue\n");
                    else
                        printf("priority queue\n");
                }
            }
        }
    }
    return 0;
}
