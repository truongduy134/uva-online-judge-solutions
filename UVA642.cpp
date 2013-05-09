#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

#define NUM_ALPHABET 26
#define MAX_LEN 100
#define END_PART "XXXXXX"
#define OUTPUT_SEPARATE "******"

void prepareMapEncodeFreqToString(vector<string> & dictionary, 
	map<string, vector<string> > & mapEncodeFreqToString);
void encodeStringByCharFreq(const string & word, string & encodeWord);

int main(void)
{
	vector<string> dictionary;
	char word[MAX_LEN + 1];
	
	// Read dictionary
	while(1)
	{
		scanf("%s", word);
		if(strcmp(word, END_PART) == 0)
			break;

		dictionary.push_back(word);
	}

	// Prepare map
	map<string, vector<string> > mapEncodeFreqToString;
	prepareMapEncodeFreqToString(dictionary, mapEncodeFreqToString);

	string encodeFreq;
	map<string, vector<string> >::const_iterator it;
	while(1)
	{
		scanf("%s", word);
		if(strcmp(word, END_PART) == 0)
			break;

		encodeStringByCharFreq(word, encodeFreq);

		it = mapEncodeFreqToString.find(encodeFreq);
		if(it == mapEncodeFreqToString.end())
			printf("NOT A VALID WORD\n");
		else
		{
			const vector<string> & output = it->second;
			printf("%s\n", output[0].c_str());
			for(int ind = 1; ind < (int) output.size(); ind++)
				printf("%s\n", output[ind].c_str());
		}
		printf("%s\n", OUTPUT_SEPARATE);
	}
	return 0;
}

void prepareMapEncodeFreqToString(vector<string> & dictionary, 
	map<string, vector<string> > & mapEncodeFreqToString)
{
	sort(dictionary.begin(), dictionary.end());

	string encodeFreq;
	map<string, vector<string> >::iterator it;

	for(int ind = 0; ind < (int) dictionary.size(); ind++)
	{
		encodeStringByCharFreq(dictionary[ind], encodeFreq);

		it = mapEncodeFreqToString.find(encodeFreq);
		if(it == mapEncodeFreqToString.end())
		{
			vector<string> newStrList;
			newStrList.push_back(dictionary[ind]);
			mapEncodeFreqToString[encodeFreq] = newStrList;
		}
		else
		{
			it->second.push_back(dictionary[ind]);
		}	
	}
}
// Assumption: word contains lowercase English alphabets only.
void encodeStringByCharFreq(const string & word, string & encodeWord)
{
	encodeWord = "";

	// Get frequencies of characters
	int freqTable[NUM_ALPHABET] = {0};
	char strNum[MAX_LEN + 1];

	for(int ind = 0; ind < (int) word.length(); ind++)
		freqTable[(int) word[ind] - 'a']++;


	for(int ind = 0; ind < NUM_ALPHABET; ind++)
		if(freqTable[ind] > 0)
		{
			encodeWord += (char) (ind + 'a');
			sprintf(strNum, "%d", freqTable[ind]);
			encodeWord += strNum;
		}
}
