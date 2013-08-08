#include <cstdio>
#include <set>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;

#define MAX_LEN_LINE 1000000

void parseLineToGetWords(char line[], set<string> & dictionary, string & leftOver);
void getListStandardWords(char line[], vector<string> & wordVect);

int main(void)
{
    set<string> dictionary;
    string leftOver;
    char line[MAX_LEN_LINE + 1];

    leftOver = "";
    while(gets(line) != NULL)
    {
        if(line[0] == '\0')
            continue;

        parseLineToGetWords(line, dictionary, leftOver);
    }

    for(set<string>::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
        printf("%s\n", it->c_str());

    return 0;
}

void parseLineToGetWords(char line[], set<string> & dictionary, string & leftOver)
{
    vector<string> wordVect;
    bool trailingHyphen;

    trailingHyphen = false;
    int strLength = (int) strlen(line);
    if(line[strLength - 1] == '-')
        trailingHyphen = true;

    getListStandardWords(line, wordVect);

    if(wordVect.size() == 0)
        return;

    string word = leftOver;
    word += wordVect[0];
    wordVect[0] = word;
    leftOver = "";

    for(int ind = 0; ind < (int) wordVect.size() - 1; ind++)
        dictionary.insert(wordVect[ind]);

    if(trailingHyphen)
    {
        leftOver = wordVect[wordVect.size() - 1];
        leftOver.erase(leftOver.end() - 1);
    }
    else
        dictionary.insert(wordVect[wordVect.size() - 1]);
}

void getListStandardWords(char str[], vector<string> & wordVect)
{
    string standardWord;

    for(int len = 0; str[len] != '\0'; len++)
        if(isalpha(str[len]) || str[len] == '-')
        {
            if(str[len] != '-')
                str[len] = tolower(str[len]);
            standardWord.push_back(str[len]);
        }
        else
        {
            // End of a word
            if(standardWord.length() > 0)
                wordVect.push_back(standardWord);
            standardWord = "";
        }

     if(standardWord.length() > 0)
        wordVect.push_back(standardWord);
}
