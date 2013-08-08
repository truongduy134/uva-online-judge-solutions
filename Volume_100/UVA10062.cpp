#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

#define MAX_NUM_CHAR 256
#define MAX_LEN_LINE 1000
#define LOWER_BOUND 32
#define UPPER_BOUND 127

void sortFreq(char line[], vector<pair<int, int> > & charAndFreqVect);
bool compareCharFreqPair(const pair<int, int> & one, const pair<int, int> & two);

int main(void)
{
    char line[MAX_LEN_LINE + 1];
    vector<pair<int, int> > charAndFreqVect;
    bool isFirst = true;

    while(gets(line) != NULL)
    {
        sortFreq(line, charAndFreqVect);

        if(isFirst)
            isFirst = false;
        else
            printf("\n");

        for(int i = 0; i < (int) charAndFreqVect.size(); i++)
            printf("%d %d\n", charAndFreqVect[i].first, charAndFreqVect[i].second);
    }
    return 0;
}

void sortFreq(char line[], vector<pair<int, int> > & charAndFreqVect)
{
    int freqTable[MAX_NUM_CHAR] = {0};

    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] >= LOWER_BOUND && line[i] <= UPPER_BOUND)
            freqTable[(int) line[i]]++;

    charAndFreqVect.clear();
    for(int i = LOWER_BOUND; i <= UPPER_BOUND; i++)
        if(freqTable[i])
            charAndFreqVect.push_back(pair<int, int> (i, freqTable[i]));

    sort(charAndFreqVect.begin(), charAndFreqVect.end(), compareCharFreqPair);
}

bool compareCharFreqPair(const pair<int, int> & one, const pair<int, int> & two)
{
    if(one.second < two.second)
        return true;
    if(one.second > two.second)
        return false;

    return one.first > two.first;
}
