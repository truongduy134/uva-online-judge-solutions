/***************************************************
 * Author: Nguyen Truong Duy
 ***************************************************/

#include <stdio.h>
#include <string.h>

#define WALL '*'
#define MAX_SIZE 60
#define MAX_LEN_LINE 100000
#define TURN_RIGHT 'R'
#define TURN_LEFT 'L'
#define FORWARD 'F'
#define QUIT 'Q'
#define NUM_DIRECTION 4

/* Trick:
 *	+ Assign 0, 1, 2, 3 to direction NORTH, EAST, SOUTH, WEST in a clockwise manner
 *	+ So turning right from direction n results in the direction (n + 1) % 4.
 *	+ Similar to turning left.
 */
enum DIRECTION {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

typedef struct
{
	int row, col;
	enum DIRECTION direction;
} Robot;

const int DIRECTION_OFFSET[NUM_DIRECTION][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void forward(char maze[][MAX_SIZE + 1], int numRow, int numCol, Robot *robot);
char getDirectionChar(enum DIRECTION direct);
void executeLineCommand(char line[], char maze[MAX_SIZE][MAX_SIZE + 1], int numRow, int numCol, Robot * robot);
void turnDirection(Robot *robot, int turnDirection);

int main(void)
{
	int T, numRow, numCol, row;
	char maze[MAX_SIZE][MAX_SIZE + 1], line[MAX_LEN_LINE + 1], trash[MAX_SIZE + 1];
	Robot robot;

	scanf("%d", &T);
	gets(trash);
	gets(trash);	/* Omit the empty line */

	while(T)
	{
		scanf("%d %d", &numRow, &numCol);
		gets(trash);

		for(row = 0; row < numRow; row++)
			gets(maze[row]);

		scanf("%d %d", &robot.row, &robot.col);
		gets(trash);

		robot.row--;
		robot.col--;
		robot.direction = NORTH;

		while(gets(line) != NULL)
		{
			if(line[0] == '\0')
				break;

			executeLineCommand(line, maze, numRow, numCol, &robot);
		}

		printf("%d %d %c\n", robot.row + 1, robot.col + 1, getDirectionChar(robot.direction));

		if(T != 1)
			printf("\n");
		T--;
	}
	return 0;
}

char getDirectionChar(enum DIRECTION direct)
{
	if(direct == NORTH)
		return 'N';
	if(direct == SOUTH)
		return 'S';
	if(direct == WEST)
		return 'W';
	return 'E';
}

void executeLineCommand(char line[], char maze[][MAX_SIZE + 1], int numRow, int numCol, Robot * robot)
{
	char * token, delim[] = " ";
	int i, flagStop;

	token = strtok(line, delim);
	while(token != NULL)
	{
		flagStop = 0;
		for(i = 0; token[i] != '\0' && !flagStop; i++)
			switch(token[i])
			{
				case QUIT:
					flagStop = 1;
					break;
				case TURN_LEFT:
					turnDirection(robot, TURN_LEFT);
					break;
				case TURN_RIGHT:
					turnDirection(robot, TURN_RIGHT);
					break;
				case FORWARD:
					forward(maze, numRow, numCol, robot);
					break;
			}

		if(flagStop)
			break;

		token = strtok(NULL, delim);
	}
}

void turnDirection(Robot *robot, int turnDirection)
{
	if(turnDirection == TURN_LEFT)
	{
		if(robot->direction == NORTH)
			robot->direction = WEST;
		else
			robot->direction--;
	}
	else
	{
		if(robot->direction == WEST)
			robot->direction = NORTH;
		else
			robot->direction++;
	}
}

void forward(char maze[][MAX_SIZE + 1], int numRow, int numCol, Robot *robot)
{
	int direction = robot->direction, nextRow, nextCol;

	nextRow = robot->row + DIRECTION_OFFSET[direction][0];
	nextCol = robot->col + DIRECTION_OFFSET[direction][1];

	if(nextRow < 0 || nextCol < 0 || nextRow >= numRow || nextCol >= numCol ||
	   maze[nextRow][nextCol] == WALL)
		return;

	robot->row = nextRow;
	robot->col = nextCol;
}
