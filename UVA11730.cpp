#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

#define MAX 1001

void findPrime(int, vector<int> &);
void findPrimeFactor(int, vector<int> &, vector<int> &);
int findNumStepTransform(int, int, vector<int> &);

int main()
{
    int curCase = 1;

    vector<int> primeList;
    findPrime(MAX / 2, primeList);

    do
    {
        int source, dest;
        cin >> source >> dest;

        if(source == 0 && dest == 0)
            break;

        cout << "Case " << curCase << ": " << findNumStepTransform(source, dest, primeList) << endl;

        curCase++;
    } while(1);

    return 0;
}

void findPrime(int limit, vector<int> & primeList)
{
    vector<bool> primeSieve(limit, true);

    for(int num = 2; num < limit; num++)
        if(primeSieve[num])
        {
            primeList.push_back(num);

            for(int multiple = num + num; multiple < limit; multiple += num)
                primeSieve[multiple] = false;
        }
}

int findNumStepTransform(int source, int dest, vector<int> & primeList)
{
    queue<pair<int, int> > queueNum;
    vector<bool> visited(MAX, false);

    queueNum.push(make_pair(source, 0));
    visited[source] = true;

    while(!queueNum.empty())
    {
        pair<int, int> curState = queueNum.front();
        queueNum.pop();

        if(curState.first == dest)
            return curState.second;

        visited[curState.first] = true;

        vector<int> primeFactorList;
        findPrimeFactor(curState.first, primeList, primeFactorList);

        int numFactor = primeFactorList.size();
        for(int index = 0; index < numFactor; index++)
        {
            int nextNum = curState.first + primeFactorList[index];

            if(nextNum <= dest && visited[nextNum] == false)
                queueNum.push(make_pair(nextNum, curState.second + 1));
        }
    }

    return -1;
}

// primeList: a vector of primes less than or equal to num / 2
void findPrimeFactor(int num, vector<int> & primeList, vector<int> & primeFactorList)
{
    int numPrime = primeList.size();
    for(int index = 0; index < numPrime && 2 * primeList[index] <= num; index++)
        if(num % primeList[index] == 0)
            primeFactorList.push_back(primeList[index]);
}
