#include <cstdio>
#include <map>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

#define MAX_LEN 40
#define MAX_LEN_LINE 10000

enum COMPARATOR {LESS, GREATER, EQUAL, LESS_EQUAL, GREATER_EQUAL};

bool compare(int left, int right, enum COMPARATOR comparator)
{
    switch(comparator)
    {
        case LESS:
            return left < right;
        case GREATER:
            return left > right;
        case EQUAL:
            return left == right;
        case LESS_EQUAL:
            return left <= right;
        default:
            return left >= right;
    }
}

int main(void)
{
    int numParty, numGuess, votePercent, leftSide, rightSide, guessNo;
    map<string, int> mapPartyToVote;
    char party[MAX_LEN], voteStr[MAX_LEN], trash[MAX_LEN], line[MAX_LEN_LINE], *token, delim[] = " +";
    enum COMPARATOR comparator;
    bool flagReadLeft;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    scanf("%d %d", &numParty, &numGuess);

    for(int i = 0; i < numParty; i++)
    {
        scanf("%s %s", party, voteStr);
        string partyName(party);
        votePercent = 0;
        for(int k = 0; voteStr[k] != '\0'; k++)
            if(isdigit(voteStr[k]))
                votePercent = votePercent * 10 + voteStr[k] - '0';
        mapPartyToVote[partyName] = votePercent;
    }

    gets(trash);

    for(int i = 0, guessNo = 1; i < numGuess; i++, guessNo++)
    {
        gets(line);

        flagReadLeft = true;

        token = strtok(line, delim);
        leftSide = 0;
        do
        {
            if(!isalnum(token[0]))
            {
                flagReadLeft = false;       // Reach comparator. Now read the right side next

                if(token[0] == '<')
                {
                    if(token[1] == '\0')
                        comparator = LESS;
                    else
                        comparator = LESS_EQUAL;
                }
                else
                {
                    if(token[0] == '>')
                    {
                        if(token[1] == '\0')
                            comparator = GREATER;
                        else
                            comparator = GREATER_EQUAL;
                    }
                    else
                        comparator = EQUAL;
                }
            }
            else
            {
                if(flagReadLeft)
                {
                    string partyName(token);
                    leftSide += mapPartyToVote[partyName];
                }
                else
                    rightSide = atoi(token) * 10;
            }

            token = strtok(NULL, delim);
        } while(token != NULL);

        if(compare(leftSide, rightSide, comparator))
            printf("Guess #%d was correct.\n", guessNo);
        else
            printf("Guess #%d was incorrect.\n", guessNo);
    }

    return 0;
}
