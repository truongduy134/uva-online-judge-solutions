#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

class Query {
public:
    int id, period, curtime;

    Query(): id(0), period(0), curtime(0) {}
    Query(int _id, int _period, int _curtime): id(_id), period(_period), curtime(_curtime) {}
    Query(const Query & obj): id(obj.id), period(obj.period), curtime(obj.curtime) {}
};

class ComparePair {
public:
    bool operator() (const Query &One, const Query &Two)
    {
        if(One.curtime < Two.curtime)
            return false;
        if(One.curtime == Two.curtime)
            if(One.id < Two.id)
                return false;

        return true;
    }
};

int main(void)
{
  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    priority_queue<Query, vector<Query>, ComparePair> queryQueue;
    char trash[100];
    int queryNum, period, id;

    while(1)
    {
        scanf("%s", trash);
        if(trash[0] == '#')
        {
            scanf("%d", &queryNum);
            break;
        }

        scanf("%d %d", &id, &period);
    //    printf("Input = %s %d %d\n", trash, id, period);
        Query query(id, period, period);
        queryQueue.push(query);
    }

    int numTaken = 0;
    while(numTaken < queryNum)
    {
        Query nxtQuery = queryQueue.top();
     //   printf("Query obj = %d %d %d\n", nxtQuery.id, nxtQuery.period, nxtQuery.curtime);
        queryQueue.pop();
        printf("%d\n", nxtQuery.id);
        nxtQuery.curtime += nxtQuery.period;
        queryQueue.push(nxtQuery);
// printf("Query obj = %d %d %d\n", nxtQuery.id, nxtQuery.period, nxtQuery.curtime);
        numTaken++;
    }
    return 0;
}

