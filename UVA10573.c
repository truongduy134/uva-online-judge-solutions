#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_LINE 100
#define MAX_NUM_INPUT 2

const double PI = 2 * acos(0);

int parseInput(char line[], int input[]);
double computeCircleArea(double radius);

/* Note: When a single t is given, we assume R = r
 */
int main(void)
{
        int T, input[MAX_NUM_INPUT], numInput;
        char line[MAX_LEN_LINE + 1];
        double R, r;

        scanf("%d", &T);
        gets(line);

        while(T)
        {
            gets(line);

            numInput = parseInput(line, input);

            if(numInput == 1)
            {
                R = input[0] / 4.0;
                r = R;
            }
            else
            {
                R = (double) input[0];
                r = (double) input[1];
            }
            printf("%.4lf\n", computeCircleArea(R + r)
                       - computeCircleArea(R)
                       - computeCircleArea(r));
            T--;
        }
        return 0;
}

int parseInput(char line[], int input[])
{
    char *token, delim[] = " ";
    int numInput = 0;

    token = strtok(line, delim);
    while(token != NULL)
    {
        input[numInput] = atoi(token);
        numInput++;

        token = strtok(NULL, delim);
    }

    return numInput;
}
double computeCircleArea(double radius)
{
    return PI * radius * radius;
}
