#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

#define MAX_NUM_WORD 100
#define MAX_WORD_LENGTH 30
#define END_TEXT '#'
#define UP 0
#define LEFT 1
#define DIAGONAL 2

void constructLongestCommonSubseq(int arrIdOne[], int arrIdTwo[], int indOne, int indTwo, int solutionTable[][MAX_NUM_WORD], vector<int> & longestCommonSubseq);
int readText(map<string, int> & mapStringToId, vector<string> & mapIdToString, int arrId[]);
void findLongestCommonSubseq(int arrIdOne[], int numWordOne, int arrIdTwo[], int numWordTwo,
			vector<int> & longestCommonSubseq);
int findLongestCommonSubseqDP(int arrIdOne[], int arrIdTwo[], int indOne, int indTwo, int memoTable[][MAX_NUM_WORD], int solutionTable[][MAX_NUM_WORD]);

int main(void)
{
	map<string, int> mapStringToId;
	vector<string> mapIdToString;
	vector<int> longestCommonSubseq;
	int arrIdOne[MAX_NUM_WORD], arrIdTwo[MAX_NUM_WORD], numWordOne, numWordTwo;

	while(1)
	{
		mapStringToId.clear();
		mapIdToString.clear();
		
		numWordOne = readText(mapStringToId, mapIdToString, arrIdOne);
		if(numWordOne == 0)
			break;

		numWordTwo = readText(mapStringToId, mapIdToString, arrIdTwo);
		if(numWordTwo == 0)
			break;
		
		findLongestCommonSubseq(arrIdOne, numWordOne, arrIdTwo, numWordTwo, longestCommonSubseq);

		if(longestCommonSubseq.size())
		{
			printf("%s", mapIdToString[longestCommonSubseq[0]].c_str());
			for(int i = 1; i < (int) longestCommonSubseq.size(); i++)
				printf(" %s", mapIdToString[longestCommonSubseq[i]].c_str());
			printf("\n");		
		}		
	}

	return 0;
}

int readText(map<string, int> & mapStringToId, vector<string> & mapIdToString, int arrId[])
{
	int numWord = 0, id;
	char word[MAX_WORD_LENGTH + 1];
	map<string, int>::iterator it;

	while(scanf("%s", word) > 0)
	{
		if(word[0] == END_TEXT)
			break;
		
		it = mapStringToId.find(word);
		if(it != mapStringToId.end())
		{
			id = it->second;
		}
		else
		{
			mapIdToString.push_back(word);
			id = (int) mapIdToString.size() - 1;
			mapStringToId[word] = id;
		}
		
		arrId[numWord] = id;
		numWord++;
	}

	return numWord; 
}

void findLongestCommonSubseq(int arrIdOne[], int numWordOne, int arrIdTwo[], int numWordTwo,
			vector<int> & longestCommonSubseq)
{
	int memoTable[MAX_NUM_WORD][MAX_NUM_WORD], solutionTable[MAX_NUM_WORD][MAX_NUM_WORD];

	memset(memoTable, -1, MAX_NUM_WORD * MAX_NUM_WORD * sizeof(int));

	findLongestCommonSubseqDP(arrIdOne, arrIdTwo, numWordOne - 1, numWordTwo - 1, memoTable, solutionTable);

	longestCommonSubseq.clear();
	constructLongestCommonSubseq(arrIdOne, arrIdTwo, numWordOne - 1, numWordTwo - 1, solutionTable, longestCommonSubseq);
}

int findLongestCommonSubseqDP(int arrIdOne[], int arrIdTwo[], int indOne, int indTwo, int memoTable[][MAX_NUM_WORD], int solutionTable[][MAX_NUM_WORD])
{
	if(indOne < 0 || indTwo < 0)
		return 0;

	if(memoTable[indOne][indTwo] >= 0)
		return memoTable[indOne][indTwo];

	int length;
	int maxLength = findLongestCommonSubseqDP(arrIdOne, arrIdTwo, indOne - 1, indTwo, memoTable, solutionTable);
	solutionTable[indOne][indTwo] = UP;

	length = findLongestCommonSubseqDP(arrIdOne, arrIdTwo, indOne, indTwo - 1, memoTable, solutionTable);
	if(length > maxLength)
	{
		maxLength = length;
		solutionTable[indOne][indTwo] = LEFT;
	}

	if(arrIdOne[indOne] == arrIdTwo[indTwo])
	{
		length = 1 + findLongestCommonSubseqDP(arrIdOne, arrIdTwo, indOne - 1, indTwo - 1, memoTable, solutionTable);
		if(length > maxLength)
		{
			solutionTable[indOne][indTwo] = DIAGONAL;
			maxLength = length;
		}
	}

	memoTable[indOne][indTwo] = maxLength;
	return maxLength;
}

void constructLongestCommonSubseq(int arrIdOne[], int arrIdTwo[], int indOne, int indTwo, int solutionTable[][MAX_NUM_WORD], vector<int> & longestCommonSubseq)
{
	if(indOne < 0 || indTwo < 0)
		return;

	int newIndOne = indOne, newIndTwo = indTwo;
	if(solutionTable[indOne][indTwo] == LEFT)
		newIndTwo--;
	else
	{
		if(solutionTable[indOne][indTwo] == UP)
			newIndOne--;
		else
		{
			newIndOne--;
			newIndTwo--;
		}
	}

	constructLongestCommonSubseq(arrIdOne, arrIdTwo, newIndOne, newIndTwo, solutionTable, longestCommonSubseq);

	if(solutionTable[indOne][indTwo] == DIAGONAL)
		longestCommonSubseq.push_back(arrIdOne[indOne]);
}
