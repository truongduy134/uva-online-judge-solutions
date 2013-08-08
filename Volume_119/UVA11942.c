#include <stdio.h>

#define MAX_SIZE 10

int isOrdered(int arr[], int size);

int main(void)
{
	int arr[MAX_SIZE], T, i;
	
	scanf("%d", &T);

	printf("Lumberjacks:\n");
	while(T)
	{
		for(i = 0; i < MAX_SIZE; i++)
			scanf("%d", &arr[i]);

		if(isOrdered(arr, MAX_SIZE))
			printf("Ordered\n");
		else
			printf("Unordered\n");

		T--;
	}

	return 0;	
}

int isOrdered(int arr[], int size)
{
	int i, increase = 1, decrease = 1;

	/* Check if it is in increasing order */
	for(i = 1; i < size; i++)
		if(arr[i] < arr[i - 1])
		{
			increase = 0;
			break;
		}

	if(increase)
		return 1;

	/* Check if it is in decreasing order */
	for(i = 1; i < size; i++)
		if(arr[i] > arr[i - 1])
		{
			decrease = 0;
			break;
		}

	return decrease;
}
