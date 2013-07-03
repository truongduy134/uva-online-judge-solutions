/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Note that we only need to consider 21 exicographically consecutive permutations of the username,
 *    the eleventh (middle) of which is the username itself.
 *  + Use next_permutation and prev_permutation to generate those 21 permutations.
 *  + For each permutation i, compute the minimum absolute distance between consecutive letters D(i).
 *  + Choose the permutation k such that D(k) is largest.
 *
 *  + Time complexity: O(C * N) where N is the length of the original username string, and
 *          C is the number of permutations we consider (In this problem C = 21).
 */

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int INFINITY = 100000;
const int MAX_NUM_CONSIDER = 10;
const int MAX_LEN_STR = 40;

void findPassword(string & userName, string & password);
int computeMinConsecutiveDiff(const string & str);
int computeAbs(int x);

int main(void)
{
    char str[MAX_LEN_STR + 1];
    string password;
    string username;

    while(scanf("%s", str) > 0)
    {
        username = str;
        findPassword(username, password);
        printf("%s\n", password.c_str());
    }

    return 0;
}

void findPassword(string & userName, string & password)
{
    vector<string> option;

    option.push_back(userName);

    // Generate all possible permutation we will consider
    int numConsider = 0;
    while(numConsider < MAX_NUM_CONSIDER && next_permutation(userName.begin(), userName.end()))
    {
        option.push_back(userName);
        numConsider++;
    }

    userName = option[0];
    numConsider = 0;
    while(numConsider < MAX_NUM_CONSIDER && prev_permutation(userName.begin(), userName.end()))
    {
        option.push_back(userName);
        numConsider++;
    }

    // Sort the result
    sort(option.begin(), option.end());

    int maxInd = 0, maxDiff = computeMinConsecutiveDiff(option[0]);
    for(int ind = 1; ind < (int) option.size(); ind++)
    {
        int diff = computeMinConsecutiveDiff(option[ind]);
        if(diff > maxDiff)
        {
            maxDiff = diff;
            maxInd = ind;
        }
    }

    char numStr[MAX_LEN_STR + 1];
    sprintf(numStr, "%d", maxDiff);
    password = option[maxInd];
    password += numStr;
}

int computeMinConsecutiveDiff(const string & str)
{
    int diff, minDiff = INFINITY;

    for(int i = 1; str[i] != '\0'; i++)
    {
        diff = computeAbs(str[i] - str[i - 1]);
        if(diff < minDiff)
            minDiff = diff;
    }

    return minDiff;
}

int computeAbs(int x)
{
    if(x < 0)
        return -x;
    return x;
}
