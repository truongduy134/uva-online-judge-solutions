#include <cstdio>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main(void)
{
    vector<pair<int, int> > vectorNumAndFreq;
    map<int, int> mapNumToInd;
    map<int, int>::iterator it;
    int n;

    while(scanf("%d", &n) > 0)
    {
        it = mapNumToInd.find(n);
        if(it == mapNumToInd.end())
        {
            vectorNumAndFreq.push_back(make_pair(n, 1));
            mapNumToInd[n] = (int) vectorNumAndFreq.size() - 1;
        }
        else
        {
            (vectorNumAndFreq[it->second].second)++;
        }
    }

    for(int i = 0; i < (int) vectorNumAndFreq.size(); i++)
        printf("%d %d\n", vectorNumAndFreq[i].first, vectorNumAndFreq[i].second);

    return 0;
}
