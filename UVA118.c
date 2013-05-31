/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Do a straight forward simulation
 *
 *  + Note: "An instruction to move "off" the world from a grid point from which a robot
 *           has been previously lost is simply ignored by the current robot."
 */

#include <stdio.h>
#include <string.h>

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
#define NUM_DIRECTION 4
int COORD_OFFSET[NUM_DIRECTION][2] = { {0, 1},        /* North */
                                       {1, 0},        /* East */
                                       {0, -1},       /* South */
                                       {-1, 0}};      /* West */

typedef struct
{
    int x, y, direction;
} Robot;

const int MAX_LEN_INSTRUCTION = 100;
const int MAX_SIZE = 51;
const char LEFT = 'L';
const char RIGHT = 'R';
const char FORWARD = 'F';
const char NORTH_CHAR = 'N';
const char EAST_CHAR = 'E';
const char SOUTH_CHAR = 'S';
const char WEST_CHAR = 'W';
const int IS_LOST = 1;
const int IS_SAFE = 0;
const int HAS_SCENT = 1;

char getDirectionChar(int direction);
char getDirectionInt(char directionC);
int executeInstruction(int maxX, int maxY, Robot * robot, char instruction[], int scentGrid[][MAX_SIZE]);
void turnLeft(Robot * robot);
void turnRight(Robot * robot);
int forward(Robot * robot, int xMax, int yMax, int scentGrid[][MAX_SIZE]);

int main(void)
{
    int maxX, maxY, isLost, scentGrid[MAX_SIZE][MAX_SIZE];
    Robot robot;
    char instruction[MAX_LEN_INSTRUCTION + 1], direction[MAX_LEN_INSTRUCTION + 1];

    memset(scentGrid, 0, MAX_SIZE * MAX_SIZE * sizeof(int));

    scanf("%d %d", &maxX, &maxY);
    while(scanf("%d %d %s", &robot.x, &robot.y, direction) > 0)
    {
        robot.direction = getDirectionInt(direction[0]);

        scanf("%s", instruction);

        isLost = executeInstruction(maxX, maxY, &robot, instruction, scentGrid);

        printf("%d %d %c", robot.x, robot.y, getDirectionChar(robot.direction));
        if(isLost == IS_LOST)
            printf(" LOST");
        printf("\n");
    }

    return 0;
}

char getDirectionChar(int direction)
{
    if(direction == NORTH)
        return NORTH_CHAR;
    if(direction == SOUTH)
        return SOUTH_CHAR;
    if(direction == WEST)
        return WEST_CHAR;
    return EAST_CHAR;
}

char getDirectionInt(char directionC)
{
    if(directionC == NORTH_CHAR)
        return NORTH;
    if(directionC == SOUTH_CHAR)
        return SOUTH;
    if(directionC == EAST_CHAR)
        return EAST;
    return WEST;
}

int executeInstruction(int maxX, int maxY, Robot * robot, char instruction[], int scentGrid[][MAX_SIZE])
{
    int i, isLost;

    for(i = 0; instruction[i] != '\0'; i++)
    {
        if(instruction[i] == LEFT)
            turnLeft(robot);
        else
        {
            if(instruction[i] == RIGHT)
                turnRight(robot);
            else
            {
                isLost = forward(robot, maxX, maxY, scentGrid);
                if(isLost == IS_LOST)
                    return IS_LOST;
            }
        }

    }

    return IS_SAFE;
}

void turnLeft(Robot * robot)
{
    int newDirection = robot->direction - 1;
    if(newDirection < 0)
        newDirection = WEST;
    robot->direction = newDirection;
}

void turnRight(Robot * robot)
{
    int newDirection = robot->direction + 1;
    if(newDirection >= NUM_DIRECTION)
        newDirection = NORTH;
    robot->direction = newDirection;
}

int forward(Robot * robot, int xMax, int yMax, int scentGrid[][MAX_SIZE])
{
    int newX = robot->x + COORD_OFFSET[robot->direction][0],
        newY = robot->y + COORD_OFFSET[robot->direction][1];

    if(newX < 0 || newY < 0 || newX > xMax || newY > yMax)
    {
        if(scentGrid[robot->x][robot->y] == HAS_SCENT)
            /* Ignore this command */
            return IS_SAFE;

        scentGrid[robot->x][robot->y] = HAS_SCENT;
        return IS_LOST;
    }
    robot->x = newX;
    robot->y = newY;
    return IS_SAFE;
}
