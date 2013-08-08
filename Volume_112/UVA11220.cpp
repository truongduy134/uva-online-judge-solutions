#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

#define MAX_LEN_LINE 100000

void decodeMessage(char line[], string & lineDecode);

int main(void)
{
	int T, caseId;
	char line[MAX_LEN_LINE];
	string messageDecode, lineDecode;

	scanf("%d", &T);
	gets(line);
	gets(line);
	caseId = 1;
	
	while(caseId <= T)
	{
		if(caseId != 1)
			printf("\n");

		messageDecode = "";

		while(1)
		{
			gets(line);
			if(line[0] == '\0')
				break;

			decodeMessage(line, lineDecode);
			messageDecode += lineDecode;
			messageDecode += "\n";			
		}

		printf("Case #%d:\n", caseId);
		printf("%s", messageDecode.c_str());

		caseId++;
	}
	return 0;
}

void decodeMessage(char line[], string & lineDecode)
{
	vector<string> wordArr;

	char *token, delim[] = " ";

	token = strtok(line, delim);
	while(token != NULL)
	{
		wordArr.push_back(token);
		token = strtok(NULL, delim);
	}

	lineDecode = "";
	int charIndex = 0;
	for(int i = 0; i < (int) wordArr.size(); i++)
	{
		if(charIndex < (int) wordArr[i].length())
		{
			lineDecode.push_back(wordArr[i][charIndex]);
			charIndex++;
		}
	}
}
