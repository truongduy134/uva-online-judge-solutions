#include <map>
#include <cstdio>
#include <string>

using namespace std;

#define END_TEST_CASE '.'
#define MAX_WORD_LEN 20

int main(void)
{
    int numJob, numWord, point, totalPoint;
    char word[MAX_WORD_LEN + 1];
    map<string, int> hayPointDictionary;
    map<string, int>::iterator it;

    //freopen("in.txt", "r", stdin);

    scanf("%d %d", &numWord, & numJob);

    for(int i = 0; i < numWord; i++)
    {
        scanf("%s %d", word, &point);
        hayPointDictionary[word] = point;
    }

    for(int i = 0; i < numJob; i++)
    {
        totalPoint = 0;

        while(1)
        {
            scanf("%s", word);
            if(word[0] == END_TEST_CASE)
                break;

            it = hayPointDictionary.find(word);
            if(it != hayPointDictionary.end())
                totalPoint += it->second;
        }

        printf("%d\n", totalPoint);
    }

    return 0;
}
