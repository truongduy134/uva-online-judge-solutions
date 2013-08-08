#include <cstdio>
#include <string>
#include <map>
#include <utility>

using namespace std;

#define MAX_LEN 100

int main(void)
{
	int numSlogan, numQuery;
	char firstLine[MAX_LEN + 2], secondLine[MAX_LEN + 2], trash[MAX_LEN + 1];
	map<string, string> mapFirstToSecondLine;

	scanf("%d", &numSlogan);
	fgets(trash, MAX_LEN + 1, stdin);
	for(int i = 0; i < numSlogan; i++)
	{
		fgets(firstLine, MAX_LEN + 2, stdin);
		fgets(secondLine, MAX_LEN + 2, stdin);
		mapFirstToSecondLine[firstLine] = secondLine;
	}

	scanf("%d", &numQuery);
	fgets(trash, MAX_LEN + 1, stdin);
	
	map<string, string>::iterator it;
	for(int i = 0; i < numQuery; i++)
	{
		fgets(firstLine, MAX_LEN + 2, stdin);
		it = mapFirstToSecondLine.find(firstLine);

		printf("%s", it->second.c_str());
	}

	return 0;	
}
