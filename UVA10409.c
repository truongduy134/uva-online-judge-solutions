#include <stdio.h>
#include <string.h>
 
#define NORTH_STR "north"
#define SOUTH_STR "south"
#define WEST_STR "west"
#define EAST_STR "east"
#define LEN_STR 10

typedef struct
{
	int topVal, northVal, westVal;
} Die;

enum DIRECTION {
	NORTH, SOUTH, WEST, EAST
};

void initDie(Die * mDie)
{
	mDie->topVal = 1;
	mDie->northVal = 2;
	mDie->westVal = 3;
}

/* Note:
 *	northFace + southFace = 7
 *	topFace + bottomFace = 7
 *	westFace + eastFace = 7
 */
void tumbleDie(Die * mDie, enum DIRECTION direct)
{
	int temp;
	switch(direct)
	{
		case NORTH:
		{
			/* south -> top
			 * top -> north
			 * west same */
			temp = mDie->topVal;
			mDie->topVal = 7 - mDie->northVal;
			mDie->northVal = temp;
			break;	
		}
		case SOUTH:
		{
			/* bottom -> north
			 * north -> top
			 * west same */
			temp = mDie->northVal;
			mDie->northVal = 7 - mDie->topVal;
			mDie->topVal = temp;
			break;
		}
		case WEST:
		{
			/* east -> top 
			 * top -> west
			 * north same */
			temp = mDie->topVal;
			mDie->topVal = 7 - mDie->westVal;
			mDie->westVal = temp;
			break;
		}
		default:
		{
			/* Case EAST
			 * west -> top
			 * bottom -> west
			 * north same */
			temp = mDie->westVal;
			mDie->westVal = 7 - mDie->topVal;
			mDie->topVal = temp;
		}
	}
}

enum DIRECTION getDirection(char directStr[])
{
	if(strcmp(directStr, NORTH_STR) == 0)
		return NORTH;
	if(strcmp(directStr, SOUTH_STR) == 0)
		return SOUTH;
	if(strcmp(directStr, WEST_STR) == 0)
		return WEST;
	return EAST;
}

int main(void)
{
	int numAct, act;
	Die mDie;
	char directStr[LEN_STR + 1];

	while(1)
	{
		scanf("%d", &numAct);
		if(numAct == 0)
			break;
	
		initDie(&mDie);

		for(act = 0; act < numAct; act++)
		{
			scanf("%s", directStr);
			
			tumbleDie(&mDie, getDirection(directStr));
		}

		printf("%d\n", mDie.topVal);
	}
	return 0;
}
