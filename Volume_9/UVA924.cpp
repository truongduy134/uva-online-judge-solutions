#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

pair<int, int> getNewsBoomDayAndAmountByBFS(const vector<vector<int> > & adjList, int sourceId);

int main(void)
{
	vector<vector<int> > adjList;
	int numV, numFriend, friendId, numQuery, sourceId;

	scanf("%d", &numV);
	adjList.assign(numV, vector<int> () );
	for(int v = 0; v < numV; v++)
	{
		scanf("%d", &numFriend);
		for(int i = 0; i < numFriend; i++)
		{
			scanf("%d", &friendId);
			adjList[v].push_back(friendId);
		}
	}

	scanf("%d", &numQuery);
	pair<int, int> result;
	for(int q = 0; q < numQuery; q++)
	{
		scanf("%d", &sourceId);

		result = getNewsBoomDayAndAmountByBFS(adjList, sourceId);

		if(result.first == 0)
			printf("%d\n", result.first);
		else
			printf("%d %d\n", result.first, result.second);
	}
	return 0;
}

pair<int, int> getNewsBoomDayAndAmountByBFS(const vector<vector<int> > & adjList, int sourceId)
{
	int numV = (int) adjList.size();

	vector<bool> heardNews(numV, false);

	queue<pair<int, int> > newsQueue;
	newsQueue.push(pair<int, int> (sourceId, 0) );
	heardNews[sourceId] = true;

	vector<int> numPeopleHeardNewsDay;
	int curId, nextId, day;

	while(!newsQueue.empty())
	{
		curId = newsQueue.front().first;
		day = newsQueue.front().second;
		newsQueue.pop();

		if(day >= (int) numPeopleHeardNewsDay.size())
			numPeopleHeardNewsDay.push_back(1);
		else
			numPeopleHeardNewsDay[day]++;

		for(int ind = 0; ind < (int) adjList[curId].size(); ind++)
		{
			nextId = adjList[curId][ind];

			if(heardNews[nextId] == false)
			{
				heardNews[nextId] = true;
				newsQueue.push(pair<int, int> (nextId, day + 1));
			}
		}
	}

	int numDay = (int) numPeopleHeardNewsDay.size();
	if(numDay < 2)
		return pair<int, int> (0, 0);

	int maxDay = 1;
	for(int day = 2; day < numDay; day++)
		if(numPeopleHeardNewsDay[day] > numPeopleHeardNewsDay[maxDay])
			maxDay = day;

	return pair<int, int> (numPeopleHeardNewsDay[maxDay], maxDay); 
}
