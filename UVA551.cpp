#include <cstdio>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

#define MAX_CHAR 3500

int findNotBalancePos(char input[]);
bool matchBracket(const string & openBracket, const string & closeBracket);

int main(void)
{
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    char input[MAX_CHAR];
    while(gets(input) != NULL)
    {
        int notBalancePos = findNotBalancePos(input);
        if(notBalancePos == 0)
            printf("YES\n");
        else
            printf("NO %d\n", notBalancePos);
    }
    return 0;
}

int findNotBalancePos(char input[])
{
    stack<string> bracketStack;
    int pos = 1;

    for(int index = 0; input[index] != '\0';)
    {
        char letter = input[index];
        string bracketStr;

        if(letter == '[' || letter == '{' || letter == '<' || letter == '(')
        {
            bracketStr.push_back(letter);
            if(letter == '(' && input[index + 1] == '*')
            {
                bracketStr.push_back(input[index + 1]);
                index += 2;
            }
            else
                index++;
            bracketStack.push(bracketStr);
        }
        else
        {
            if(letter == '*' || letter == ')' || letter == ']' || letter == '}' || letter == '>')
            {
                bool isCloseBracket = true;
                bool is2CharBracket = false;

                string closeBracket;
                closeBracket.push_back(letter);
                if(letter == '*')
                {
                    if(input[index + 1] == ')')
                    {
                        closeBracket.push_back(input[index + 1]);
                        is2CharBracket = true;
                    }
                    else
                        isCloseBracket = false;
                }

                if(isCloseBracket)
                {
                    if(bracketStack.empty())
                        return pos;
                    string openBracket = bracketStack.top();
                    bracketStack.pop();
                    if(!matchBracket(openBracket, closeBracket))
                        return pos;
                }

                if(is2CharBracket)
                    index += 2;
                else
                    index++;
            }
            else
                index++;
        }
        pos++;
    }

    if(!bracketStack.empty())
        return pos;
    return 0;
}

bool matchBracket(const string & openBracket, const string & closeBracket)
{
    if(openBracket.compare("{") == 0 && closeBracket.compare("}") == 0)
        return true;
    if(openBracket.compare("(") == 0 && closeBracket.compare(")") == 0)
        return true;
    if(openBracket.compare("[") == 0 && closeBracket.compare("]") == 0)
        return true;
    if(openBracket.compare("<") == 0 && closeBracket.compare(">") == 0)
        return true;
    if(openBracket.compare("(*") == 0 && closeBracket.compare("*)") == 0)
        return true;

    return false;
}
