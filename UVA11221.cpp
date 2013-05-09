#include <cstdio>
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>

using namespace std;

void getAlphaOnly(const string &inLine, string &txt);
int isMagicPalin(const string &txt);

int main(void)
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    int numTest, caseId;
    string inLine, trash;

    caseId = 1;
    cin >> numTest;
    getline(cin, trash);
    while(caseId <= numTest)
    {
        getline(cin, inLine);
        string txt;

        getAlphaOnly(inLine, txt);

        int sizeMat = isMagicPalin(txt);
        cout << "Case #" << caseId << ":" << endl;
        if(sizeMat)
            cout << sizeMat << endl;
        else
            cout << "No magic :(" << endl;
        caseId++;
    }
    return 0;
}

void getAlphaOnly(const string &inLine, string &txt)
{
    for(int index = 0; index < inLine.size(); index++)
        if(isalpha(inLine[index]))
            txt.push_back(inLine[index]);
}

int isMagicPalin(const string &txt)
{
    int len = txt.size();

    int squareRoot = (int) floor(sqrt(len));

    if(squareRoot * squareRoot != len)
        return 0;

    string copyStr(txt);
    // Read from (K, K) from left
    reverse(copyStr.begin(), copyStr.end());
    if(txt.compare(copyStr) != 0)
        return 0;

    char alphaMat[squareRoot][squareRoot];
    for(int i = 0, row = 0; row < squareRoot; row++)
        for(int col = 0; col < squareRoot; col++)
        {
            alphaMat[row][col] = copyStr[i];
            i++;
        }

    // Form a string by reading from (1, 1) downwards
    string nxtStr;
    for(int col = 0; col < squareRoot; col++)
        for(int row = 0; row < squareRoot; row++)
            nxtStr.push_back(alphaMat[row][col]);
    if(txt.compare(nxtStr) != 0)
        return 0;

    // Form a string by reading from (K, K) upwards
    string finalStr;
    for(int col = squareRoot - 1; col >= 0; col--)
        for(int row = squareRoot - 1; row >= 0; row--)
            finalStr.push_back(alphaMat[row][col]);
    if(txt.compare(finalStr) != 0)
        return 0;

    return squareRoot;
}
