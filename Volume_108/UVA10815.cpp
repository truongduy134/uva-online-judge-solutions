#include <cstring>
#include <cstdio>
#include <set>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

#define MAX_LEN 300

int main(void)
{

    char line[MAX_LEN], word[MAX_LEN];
    set<string> wordSet;
    int wordIndex;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);
    while(gets(line) != NULL)
    {
        wordIndex = 0;
        for(int i = 0; ; i++)
            if(isalpha(line[i]))
            {
                word[wordIndex] = tolower(line[i]);
                wordIndex++;
            }
            else
            {
                word[wordIndex] = '\0';
                if(word[0] != '\0')
                {
                    string newStr(word);
                    wordSet.insert(newStr);
                }

                if(line[i] == '\0')
                    break;
                wordIndex = 0;
            }
    }

    for(set<string>::iterator it = wordSet.begin(); it != wordSet.end(); it++)
        cout << *it << endl;

    return 0;
}
