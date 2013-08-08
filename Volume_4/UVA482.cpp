#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

#define MAX_LEN 1000000
int main(void)
{
    int T;
    char trash[10], line[MAX_LEN], *token, delim[] = " ";
    vector<int> permuteArr, mapPermuteToOrigin;
    vector<string> strArr;

   // freopen("in.txt", "r", stdin);

    scanf("%d", &T);
    gets(trash);

    while(T)
    {
        permuteArr.clear();
        strArr.clear();
        gets(trash);

        gets(line);
        token = strtok(line, delim);
        do
        {
            permuteArr.push_back(atoi(token) - 1);
            token = strtok(NULL, delim);
        } while(token != NULL);

        gets(line);
        token = strtok(line, delim);
        do
        {
            strArr.push_back(token);
            token = strtok(NULL, delim);
        } while(token != NULL);

        mapPermuteToOrigin.assign(permuteArr.size(), 0);
        for(int i = 0; i < (int) permuteArr.size(); i++)
            mapPermuteToOrigin[permuteArr[i]] = i;

        for(int i = 0; i < (int) permuteArr.size(); i++)
            printf("%s\n", strArr[mapPermuteToOrigin[i]].c_str());

        if(T != 1)
            printf("\n");
        T--;
    }
    return 0;
}
