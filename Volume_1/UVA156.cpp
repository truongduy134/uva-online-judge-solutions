#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>

using namespace std;

bool areAnagrams(const string & s1, const string & s2);
void getEachWord(vector<string> & wordArr, string & line);
void selectAnanagram(vector<string> & ananagramVector, vector<string> & wordVector);

int main()
{
    vector<string> wordVector, ananagramVector;
    string line;

    // Read words from standard input
    while(1)
    {
        getline(cin, line);
        if(line[0] == '#')
            break;      // End of input

        // Parse input to get words
        getEachWord(wordVector, line);
    }

    // Select ananagrams
    selectAnanagram(ananagramVector, wordVector);

    // Sort the result vectors
    sort(ananagramVector.begin(), ananagramVector.end());

    // Output
    for(int index = 0; index < ananagramVector.size(); index++)
        cout << ananagramVector[index] << endl;
    return 0;
}

bool areAnagrams(const string & s1, const string & s2)
{
    const int NUM_ALPHA = 26;
    int numLetter[NUM_ALPHA] = {0};

    for(int index = 0; index < s1.length(); index++)
        numLetter[tolower(s1[index]) - 'a']++;
    for(int index = 0; index < s2.length(); index++)
        numLetter[tolower(s2[index]) - 'a']--;

    for(int index = 0; index < NUM_ALPHA; index++)
        if(numLetter[index])
            return false;
    return true;
}

void getEachWord(vector<string> & wordArr, string & line)
{
    stringstream strInput(line, stringstream::in);
    string word;

    while(!strInput.eof())
    {
        strInput >> word;
        wordArr.push_back(word);
    }
}

void selectAnanagram(vector<string> & ananagramVector, vector<string> & wordVector)
{
    vector<bool> needCheckVector(wordVector.size(), true);

    for(int index = 0; index < wordVector.size(); index++)
        if(needCheckVector[index])
        {
            bool isAnanagram = true;

            for(int another = index + 1; another < wordVector.size(); another++)
                if(needCheckVector[another])
                {
                    if(areAnagrams(wordVector[index], wordVector[another]))
                    {
                        isAnanagram = false;
                        needCheckVector[another] = false;
                    }
                }

            if(isAnanagram)
                ananagramVector.push_back(wordVector[index]);
            needCheckVector[index] = false;

        }
}
