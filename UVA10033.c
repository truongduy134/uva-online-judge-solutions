#include <stdio.h>
#include <string.h>

#define MOD_VAL 1000
#define NUM_REGISTER 10
#define SIZE_RAM 1000
#define LEN_INSTRUCTION 3

void executeInstruction(int mRegister[], int mRAM[], int *programCounter, int *isHalt);
void splitIntoDigit(int digitArr[], int n);

int main(void)
{
	int mRegister[NUM_REGISTER], mRAM[SIZE_RAM], T, numInstruction, isHalt, ind, j,
		programCounter;
	char instruction[LEN_INSTRUCTION + 2], trash[LEN_INSTRUCTION + 2];

	scanf("%d", &T);
	fgets(trash, LEN_INSTRUCTION + 2, stdin);
	fgets(trash, LEN_INSTRUCTION + 2, stdin);

	while(T)
	{
		memset(mRAM, 0, SIZE_RAM * sizeof(int));
		memset(mRegister, 0, NUM_REGISTER * sizeof(int));
		numInstruction = 0;
		isHalt = 0;
		programCounter = 0;
		ind = 0;
		while(1)
		{
			if(fgets(instruction, LEN_INSTRUCTION + 2, stdin) == NULL)
				break;
			if(instruction[0] == '\n' || instruction[0] == '\0')
				break;
	
			for(j = 0; j < LEN_INSTRUCTION; j++)
				mRAM[ind] = mRAM[ind] * 10 + (instruction[j] - '0');
			ind++;
		}
		
		while(!isHalt && programCounter < SIZE_RAM)
		{
			executeInstruction(mRegister, mRAM, &programCounter, &isHalt);
			numInstruction++;
		}

		printf("%d\n", numInstruction);
		if(T != 1)
			printf("\n");
		T--;
	}

	return 0;
}

void executeInstruction(int mRegister[], int mRAM[], int *programCounter, int *isHalt)
{
	int instruction[LEN_INSTRUCTION], isJump;

	splitIntoDigit(instruction, mRAM[*programCounter]);

	isJump = 0;
	switch(instruction[0])
	{
		case 1:
			*isHalt = 1;
			break;
		case 2:
			mRegister[instruction[1]] = instruction[2];
			break;
		case 3:
			mRegister[instruction[1]] += instruction[2];
			mRegister[instruction[1]] %= MOD_VAL;
			break;
		case 4:
			mRegister[instruction[1]] *= instruction[2];
			mRegister[instruction[1]] %= MOD_VAL;
			break;
		case 5:
			mRegister[instruction[1]] = mRegister[instruction[2]];
			break;
		case 6:
			mRegister[instruction[1]] += mRegister[instruction[2]];
			mRegister[instruction[1]] %= MOD_VAL;
			break;
		case 7:
			mRegister[instruction[1]] *= mRegister[instruction[2]];
			mRegister[instruction[1]] %= MOD_VAL;
			break;
		case 8:
			mRegister[instruction[1]] = mRAM[mRegister[instruction[2]]];
			break;
		case 9:
			mRAM[mRegister[instruction[2]]] = mRegister[instruction[1]];
			break;
		case 0:
			if(mRegister[instruction[2]] != 0)
			{
				*programCounter = mRegister[instruction[1]];
				isJump = 1;
			}
	}

	if(!isJump)
		(*programCounter)++;
}

void splitIntoDigit(int digitArr[], int n)
{
	int ind = LEN_INSTRUCTION - 1;

	while(ind >= 0)
	{
		digitArr[ind] = n % 10;
		n /= 10;
		ind--;
	}
}
