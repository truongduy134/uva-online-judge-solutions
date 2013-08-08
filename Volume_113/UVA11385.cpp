#include <cstdio>
#include <map>
#include <climits>
#include <cctype>
#include <cstring>

using namespace std;

#define MAX_LEN 300
#define MAX_SIZE 200

void generateFiboIndexMap(map<int, int> & mapFiboToIndex);
void decodeMessage(char encodeStr[], char decodeStr[], int fiboArr[], int numFibo, const map<int, int> & mapFiboToIndex);

int main(void)
{
	map<int, int> mapFiboToIndex;
	int fiboArr[MAX_SIZE], T, numFibo;
	char encodeStr[MAX_LEN + 1], decodeStr[MAX_LEN + 1],
		trash[MAX_LEN + 1];
	
	generateFiboIndexMap(mapFiboToIndex);

	scanf("%d", &T);
	while(T)
	{
		scanf("%d", &numFibo);
		for(int i = 0; i < numFibo; i++)
			scanf("%d", &fiboArr[i]);
		fgets(trash, MAX_LEN + 1, stdin);

		fgets(encodeStr, MAX_LEN + 1, stdin);

		decodeMessage(encodeStr, decodeStr, fiboArr, numFibo, mapFiboToIndex);

		printf("%s\n", decodeStr);
		T--;
	}

	return 0;
}

void generateFiboIndexMap(map<int, int> & mapFiboToIndex)
{
	mapFiboToIndex.clear();

	int fiboOne = 1, fiboTwo = 2, fibo, fiboInd = 1;
	mapFiboToIndex[fiboOne] = fiboInd;
	fiboInd++;
	mapFiboToIndex[fiboTwo] = fiboInd;
	fiboInd++;

	
	while(fiboOne <= LONG_MAX - fiboTwo)
	{
		fibo = fiboOne + fiboTwo;
		mapFiboToIndex[fibo] = fiboInd;
		fiboInd++;
		fiboOne = fiboTwo;
		fiboTwo = fibo;
	}
}

void decodeMessage(char encodeStr[], char decodeStr[], int fiboArr[], int numFibo, const map<int, int> & mapFiboToIndex)
{
	int indEncode, indDecode, indFibo, maxLen;

	memset(decodeStr, ' ', MAX_LEN * sizeof(char));

	for(indEncode = 0, indFibo = 0, maxLen = 0; 
			encodeStr[indEncode] != '\0' && indFibo < numFibo; indEncode++)
	{
		if(isupper(encodeStr[indEncode]))
		{
			indDecode = mapFiboToIndex.find(fiboArr[indFibo])->second;
			indFibo++;

			decodeStr[indDecode - 1] = encodeStr[indEncode];

			if(indDecode > maxLen)
				maxLen = indDecode;
		}
	}

	decodeStr[maxLen] = '\0';
}
