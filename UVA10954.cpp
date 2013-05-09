#include <cstdio>
#include <queue>

using namespace std;

int main(void)
{
    int N, input, numOne, numTwo, cost;
    priority_queue<int> queueInt;

//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    while(1)
    {
        scanf("%d", &N);
        if(N == 0)
            break;

        for(int i = 0; i < N; i++)
        {
            scanf("%d", &input);
            queueInt.push(-input);      // Turn to min heap
        }

        cost = 0;
        while(queueInt.size() >= 2)
        {
            numOne = queueInt.top();
            queueInt.pop();
            numTwo = queueInt.top();
            queueInt.pop();
            cost += numOne + numTwo;
            queueInt.push(numOne + numTwo);
        }

        printf("%d\n", -cost);
        queueInt.pop();     // Now queue are empty
    }
}
