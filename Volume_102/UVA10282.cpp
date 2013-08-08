#include <cstdio>
#include <map>
#include <string>

using namespace std;

#define MAX_LEN 50

int main(void)
{
	map<string, string> foreignToEnglishMap;
	char line[2 * MAX_LEN + 1], foreignWord[MAX_LEN + 1], englishWord[MAX_LEN + 1];
	map<string, string>::iterator it;

	while(1)
	{
		gets(line);
		if(line[0] == '\0')
			break;

		sscanf(line, "%s %s", englishWord, foreignWord);
		foreignToEnglishMap[foreignWord] = englishWord;
	}

	while(scanf("%s", foreignWord) > 0)
	{
		it = foreignToEnglishMap.find(foreignWord);

		if(it == foreignToEnglishMap.end())
			printf("eh\n");
		else
			printf("%s\n", it->second.c_str());		
	}

	return 0;
}
