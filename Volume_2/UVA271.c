#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

int isSentence(char str[], int start, int end, int memoTable[][MAX_LEN]);

int main(void)
{
	char str[MAX_LEN + 1];
	int memoTable[MAX_LEN][MAX_LEN];

	while(scanf("%s", str) > 0)
	{
		memset(memoTable, -1, MAX_LEN * MAX_LEN * sizeof(int));

		if(isSentence(str, 0, (int) strlen(str) - 1, memoTable))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}

int isSentence(char str[], int start, int end, int memoTable[][MAX_LEN])
{
	int len = end - start + 1, k, result;

	if(len == 0)
		return 0;

	if(len == 1)
	{
		if(str[start] >= 'p' && str[end] <= 'z')
			return 1;
		return 0;
	}
	
	if(memoTable[start][end] >= 0)
		return memoTable[start][end];

	result = 0;
	if(str[start] == 'N')
		result = isSentence(str, start + 1, end, memoTable);
	else
	{
		if(str[start] == 'C' || str[start] == 'D' || str[start] == 'E' || str[start] == 'I')
		{
			for(k = start + 1; k <= end; k++)
			{
				result = isSentence(str, start + 1, k, memoTable) && isSentence(str, k + 1, end, memoTable);
				if(result)
					break;
			}
		}
	} 

	memoTable[start][end] = result; 
	return result;
}
