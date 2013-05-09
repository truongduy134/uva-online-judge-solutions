#include <stdio.h>
#include <string.h>

#define IF_BLOCK 0
#define ELSE_BLOCK 1
#define IF_KEYWORD "IF"
#define ELSE_KEYWORD "ELSE"
#define ENDIF_KEYWORD "END_IF"
#define NON_BRANCH_KEYWORD "S"
#define END_PROGRAM "ENDPROGRAM"
#define MAX_LEN 100

int readProgramAndCount();
int readConditionBlockAndCount(int level, int kind_block);

int main(void)
{
	int numProgram, level;

	scanf("%d", &numProgram);
	
	while(numProgram)
	{
		printf("%d\n", readProgramAndCount());
		numProgram--;
	}

	return 0;
}

int readProgramAndCount()
{
	char word[MAX_LEN + 1];
	int count = 1;

	while(1)
	{
		scanf("%s", word);
		if(strcmp(word, END_PROGRAM) == 0)
			break;

		if(strcmp(word, NON_BRANCH_KEYWORD) == 0)
			continue;

		/* Then it is the if block. We assume the input is valid */
		count *= readConditionBlockAndCount(0, IF_BLOCK);	
	}

	return count;
}

int readConditionBlockAndCount(int level, int kind_block)
{
	char word[MAX_LEN + 1];
	int count = 1;

	while(1)
	{
		scanf("%s", word);
		if(strcmp(word, NON_BRANCH_KEYWORD) == 0)
			continue;
	
		if(kind_block == IF_BLOCK && strcmp(word, ELSE_KEYWORD) == 0)
			break;
		if(kind_block == ELSE_BLOCK && strcmp(word, ENDIF_KEYWORD) == 0)
			break;

		if(strcmp(word, IF_KEYWORD) == 0)
			count *= readConditionBlockAndCount(level + 1, IF_BLOCK);
	}

	if(strcmp(word, ELSE_KEYWORD) == 0)
		count += readConditionBlockAndCount(level + 1, ELSE_BLOCK);
	
	return count;
}
