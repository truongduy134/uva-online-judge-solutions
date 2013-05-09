#include <stdio.h>
#include <ctype.h>

#define MAX_LEN_LINE 1000000
#define SPACE_SIGNAL 'b'
#define END_OF_LINE_SIGNAL '!'

int main(void)
{
	char line[MAX_LEN_LINE + 1], output_maze[MAX_LEN_LINE + 1];
	int ind, outputInd, freq, printChar;

	while(fgets(line, MAX_LEN_LINE + 1, stdin) != NULL)
	{
		ind = 0;
		outputInd = 0;
		freq = 0;
		for(ind = 0; line[ind] != '\0'; ind++)
		{
			if(isdigit(line[ind]))
			{
				freq += (line[ind] - '0');
			}
			else
			{
				printChar = line[ind];
				if(line[ind] == SPACE_SIGNAL)
					printChar = ' ';
				else
					if(line[ind] == END_OF_LINE_SIGNAL)
					{
						printChar = '\n';
						freq = 1;
					}
	
				for(; freq > 0; freq--)
				{
					output_maze[outputInd] = printChar;
					outputInd++;
				}
			}	
		}
		output_maze[outputInd] = '\n';
		outputInd++;
		output_maze[outputInd] = '\0';
		outputInd++;

		printf("%s", output_maze);				
	} 
	return 0;
}
