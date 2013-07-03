/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <set>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

const int MAX_LEN_LINE = 70;

void getLowercaseWordList(const string & str, vector<string> & wordList);
void getWorstExcuseIndList(const set<string> & keywordSet, const vector<string> & excuseList,
                           vector<int> & indList);

int main(void)
{
    int numKeyword, numExcuse;
    vector<string> excuseList;
    vector<int> indList;
    set<string> keywordSet;
    char line[MAX_LEN_LINE + 1];
    int caseId = 1;

    while(scanf("%d %d", &numKeyword, &numExcuse) > 0)
    {
        excuseList.clear();
        keywordSet.clear();

        for(int i = 0; i < numKeyword; i++)
        {
            scanf("%s", line);
            keywordSet.insert(line);
        }

        gets(line); // Get rid of trailing \n
        for(int i = 0; i < numExcuse; i++)
        {
            gets(line);
            excuseList.push_back(line);
        }

        getWorstExcuseIndList(keywordSet, excuseList, indList);

        printf("Excuse Set #%d\n", caseId);
        for(int i = 0; i < (int) indList.size(); i++)
            printf("%s\n", excuseList[indList[i]].c_str());
        printf("\n");

        caseId++;
    }
    return 0;
}

void getWorstExcuseIndList(const set<string> & keywordSet, const vector<string> & excuseList,
                           vector<int> & indList)
{
    int numExcuse = (int) excuseList.size();
    vector<int> numKeywordContained(numExcuse, 0);

    for(int i = 0; i < numExcuse; i++)
    {
        vector<string> wordList;
        getLowercaseWordList(excuseList[i], wordList);

        for(int wordId = 0; wordId < (int) wordList.size(); wordId++)
            if(keywordSet.find(wordList[wordId]) != keywordSet.end())
                numKeywordContained[i]++;
    }

    int maxNum = 0;
    for(int i = 0; i < numExcuse; i++)
        if(numKeywordContained[i] > maxNum)
            maxNum = numKeywordContained[i];

    indList.clear();
    for(int i = 0; i < numExcuse; i++)
        if(numKeywordContained[i] == maxNum)
            indList.push_back(i);
}

void getLowercaseWordList(const string & str, vector<string> & wordList)
{
    wordList.clear();

    int lenStr = (int) str.length();
    for(int startInd = 0; startInd < lenStr;)
        if(isalpha(str[startInd]))
        {
            int endInd = startInd;

            string newWord;

            do
            {
                newWord.push_back(tolower(str[endInd]));
                endInd++;
            } while(endInd < lenStr && isalpha(str[endInd]));

            wordList.push_back(newWord);
            startInd = endInd + 1;
        }
        else
            startInd++;
}
