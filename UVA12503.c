#include <stdio.h>
#include <string.h>

#define MAX_NUM_INSTRUCTION 100
#define MAX_LEN 100

#define LEFT "LEFT"
#define RIGHT "RIGHT"
#define SAME_AS_PREVIOUS "SAME"
#define LEFT_OFFSET -1
#define RIGHT_OFFSET 1

int main(void)
{
	int offsetInstruction[MAX_NUM_INSTRUCTION], numInstruction, T,prevId, curId, pos;
	char instruction[MAX_LEN + 1], trash[MAX_LEN + 1];

	scanf("%d", &T);

	while(T)
	{
		scanf("%d", &numInstruction);

		for(curId = 0; curId < numInstruction; curId++)
		{
			scanf("%s", instruction);

			if(strcmp(instruction, LEFT) == 0)
				offsetInstruction[curId] = -1;	
			else
			{
				if(strcmp(instruction, RIGHT) == 0)
					offsetInstruction[curId] = 1;
				else
				{
					scanf("%s %d", trash, &prevId);
					prevId--;
					offsetInstruction[curId] = offsetInstruction[prevId]; 
				}
			}
		}

		pos = 0;
		for(curId = 0; curId < numInstruction; curId++)
			pos += offsetInstruction[curId];

		printf("%d\n", pos);
		T--;
	}
	return 0; 
}
