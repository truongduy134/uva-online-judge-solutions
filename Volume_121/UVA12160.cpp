#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define MAX_VAL 10000
#define MAX_NUM_BUTTON 10

int findMinNumPress(int initState, int destState, int buttonVal[], int numButton);

int main(void)
{
	int initState, destState, numButton, buttonVal[MAX_NUM_BUTTON], minNumPress, caseId;

	caseId = 1;
	while(1)
	{
		scanf("%d %d %d", &initState, &destState, &numButton);
		if(initState == 0 && destState == 0 && numButton == 0)
			break;


		for(int i = 0; i < numButton; i++)
			scanf("%d", &buttonVal[i]);

		printf("Case %d: ", caseId);
		if((minNumPress = findMinNumPress(initState, destState, buttonVal, numButton)) < 0)
			printf("Permanently Locked\n");
		else
			printf("%d\n", minNumPress);

		caseId++;		
	}

	return 0;		
}

int findMinNumPress(int initState, int destState, int buttonVal[], int numButton)
{
	vector<bool> visited(MAX_VAL, false);
	vector<int> numPress(MAX_VAL, 0);
	queue<int> stateQueue;

	stateQueue.push(initState);
	visited[initState] = true;

	int curState, nextState;
	while(!stateQueue.empty())
	{
		curState = stateQueue.front();
		stateQueue.pop();

		if(curState == destState)
			return numPress[destState];

		for(int i = 0; i < numButton; i++)
		{
			nextState = (curState + buttonVal[i]) % MAX_VAL;
			if(!visited[nextState])
			{
				numPress[nextState] = numPress[curState] + 1;
				visited[nextState] = true;
				stateQueue.push(nextState);
			}
		} 
	}

	return -1;	
}
