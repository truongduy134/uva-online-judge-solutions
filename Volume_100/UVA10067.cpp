#include <cstdio>
#include <queue>
#include <vector>
#include <cctype>

using namespace std;

#define MAX_LEN 20
#define NUM_BUTTON 4
#define MAX_NUM_STATE 10000

int setDigitAtIndex(int num, int newDigit, int pos);
int getDigitAtIndex(int num, int pos);
int getNumFromInput();
int getMinNumPress(int initState, int destState, const vector<int> & forbiddenStates);

int main(void)
{
	int initState, destState, T, numForbidState;
	vector<int> forbiddenStates;

	scanf("%d", &T);
	
	while(T)
	{
		forbiddenStates.clear();

		initState = getNumFromInput();
		destState = getNumFromInput();

		scanf("%d", &numForbidState);

		for(int i = 0; i < numForbidState; i++)
		{
			forbiddenStates.push_back(getNumFromInput());
		}

		printf("%d\n", getMinNumPress(initState, destState, forbiddenStates));
		T--;			
	}	
	return 0;
}

int getDigitAtIndex(int num, int pos)
{
	int lastDigit;
	
	while(num != 0)
	{
		lastDigit = num % 10;
		if(pos == 0)
			return lastDigit;
		pos--;
		num /= 10;
	}	

	return 0;
}

int setDigitAtIndex(int num, int newDigit, int pos)
{
	int powerOfTen = 1, oldDigit = getDigitAtIndex(num, pos);

	while(pos)
	{
		powerOfTen *= 10;
		pos--;
	}

	return num + (newDigit - oldDigit) * powerOfTen;
}

int getNumFromInput()
{
	int num = 0, digit;

	for(int i = 0; i < NUM_BUTTON; i++)
	{
		scanf("%d", &digit);
		num = num * 10 + digit;
	} 

	return num;
}

int getMinNumPress(int initState, int destState, const vector<int> & forbiddenStates)
{
	if(initState == destState)
		return 0;

	queue<int> stateQueue;
	vector<int> minPress(MAX_NUM_STATE, -1);
	vector<bool> visited(MAX_NUM_STATE, false);

	for(int i = 0; i < (int) forbiddenStates.size(); i++)
		visited[forbiddenStates[i]] = true;

	if(visited[initState])
		return -1;

	visited[initState] = true;
	stateQueue.push(initState);
	minPress[initState] = 0;

	int curState, nextState, digit, newDigit;
	while(!stateQueue.empty())
	{
		curState = stateQueue.front();
		stateQueue.pop();

		if(curState == destState)
			return minPress[destState];

		for(int button = 0; button < NUM_BUTTON; button++)
		{
			digit = getDigitAtIndex(curState, button);

			for(int direction = -1; direction <= 1; direction += 2)
			{
				newDigit = digit + direction;
				if(newDigit > 9)
					newDigit = 0;
				if(newDigit < 0)
					newDigit = 9;

				nextState = setDigitAtIndex(curState, newDigit, button);
				if(!visited[nextState])
				{
					visited[nextState] = true;
					stateQueue.push(nextState);
					minPress[nextState] = minPress[curState] + 1;
				}
			}
		}		
	}

	return -1;	// Unreachable
}
