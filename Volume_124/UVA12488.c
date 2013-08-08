#include <stdio.h>

#define MAX_NUM 100

int getMinOverTake(int startOrder[], int lastOrder[], int N);
int findPosition(int arr[], int N, int key);

int main(void)
{
	int N, startOrder[MAX_NUM], lastOrder[MAX_NUM], i;

	while(scanf("%d", &N) > 0)
	{
		for(i = 0; i < N; i++)
		{
			scanf("%d", &startOrder[i]);
			startOrder[i]--;
		}
		for(i = 0; i < N; i++)
		{
			scanf("%d", &lastOrder[i]);
			lastOrder[i]--;
		}

		printf("%d\n", getMinOverTake(startOrder, lastOrder, N));
	}
	return 0;
}

int getMinOverTake(int startOrder[], int lastOrder[], int N)
{
	int i, pos, minTakeover = 0, posFront, front;

	for(i = 1; i < N; i++)
	{
		pos = findPosition(lastOrder, N, startOrder[i]);
		for(front = 0; front < i; front++)
		{
			posFront = findPosition(lastOrder, N, startOrder[front]);
			if(posFront > pos)
				minTakeover++;
		}
	}
	return minTakeover;
}

int findPosition(int arr[], int N, int key)
{
	int pos;

	for(pos = 0; pos < N; pos++)
		if(arr[pos] == key)
			return pos;

	return -1;
}
