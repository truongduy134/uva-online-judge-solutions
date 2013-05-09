#include <stdio.h>

#define ON 1
#define OFF 0
#define MAX_NUM_DEVICE 20

typedef struct {
	int powerConsume, state;
} Device;

int main(void)
{
	Device deviceArr[MAX_NUM_DEVICE];
	int numDevice, numOperation, deviceId, maxCapacity, maxConsume, op, consume;
	int isBlown, caseId = 1;

	while(1)
	{
		scanf("%d %d %d", &numDevice, &numOperation, &maxCapacity);
		if(!(numDevice || numOperation || maxCapacity))
			break;

		for(deviceId = 0; deviceId < numDevice; deviceId++)
		{
			scanf("%d", &deviceArr[deviceId].powerConsume);
			deviceArr[deviceId].state = OFF;
		}

		isBlown = 0;
		maxConsume = 0;
		consume = 0;

		for(op = 0; op < numOperation; op++)
		{
			scanf("%d", &deviceId);
			deviceId--;
		
			if(!isBlown)
			{
				deviceArr[deviceId].state = 1 - deviceArr[deviceId].state;

				if(deviceArr[deviceId].state == ON)
				{
					consume += deviceArr[deviceId].powerConsume;
					if(consume > maxCapacity)
						isBlown = 1;
					else
					{
						if(consume > maxConsume)
							maxConsume = consume;
					}
				}
				else
					consume -= deviceArr[deviceId].powerConsume;
			}
		}

		printf("Sequence %d\n", caseId);
		if(isBlown)
			printf("Fuse was blown.\n\n");
		else
			printf("Fuse was not blown.\nMaximal power consumption was %d amperes.\n\n", maxConsume);

		caseId++;
	}
	return 0;
}
