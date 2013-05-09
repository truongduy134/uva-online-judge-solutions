#include <cstdio>
#include <string>
#include <map>

using namespace std;

#define MAX_LEN 20

void getPluralForm(const string & singular, string & plural, const map<string, string> & mapIrregularNounToPlural);
bool mayAppendES(const string & str);
bool shouldReplaceYwithIES(const string & str);
bool isVowel(char ch);

int main(void)
{
	int numIrregular, numWord;
	char word[MAX_LEN + 1], wordTwo[MAX_LEN + 1];
	string plural;
	map<string, string> mapIrregularNounToPlural;

	scanf("%d %d", &numIrregular, &numWord);
	for(int i = 0; i < numIrregular; i++)
	{
		scanf("%s %s", word, wordTwo);
		mapIrregularNounToPlural[word] = wordTwo;
	}

	for(int i = 0; i < numWord; i++)
	{
		scanf("%s", word);
		getPluralForm(word, plural, mapIrregularNounToPlural);

		printf("%s\n", plural.c_str());
	}
	return 0;
}

void getPluralForm(const string & singular, string & plural, const map<string, string> & mapIrregularNounToPlural)
{
	map<string, string>::const_iterator it = mapIrregularNounToPlural.find(singular);
	if(it != mapIrregularNounToPlural.end())
	{
		plural = it->second;
	}
	else
	{
		plural = singular;
		if(shouldReplaceYwithIES(singular))
		{
			// Replace 'y' with 'ies'
			plural[plural.length() - 1] = 'i';
			plural += "es";
		}
		else
		{
			if(mayAppendES(singular))
				plural += "es";
			else
				plural += 's';
		}
	}
}

bool shouldReplaceYwithIES(const string & str)
{
	int length = str.length();

	if(length <= 1)
		return false;

	if(str[length - 1] == 'y' && !isVowel(str[length - 2]))
		return true;
	return false;
}

bool mayAppendES(const string & str)
{
	int length = str.length();
	
	if(length < 1)
		return false;

	if(str[length - 1] == 'o' || str[length - 1] == 's' || str[length - 1] == 'x')
		return true;
	
	if(length > 1)
	{
		if((str[length - 2] == 's' || str[length - 2] == 'c') && str[length - 1] == 'h')
			return true; 
	}

	return false;
}

bool isVowel(char ch)
{
	return (ch == 'a') || (ch == 'e') || (ch == 'i') || (ch == 'u') || (ch == 'o');
}
