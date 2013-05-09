#include <cstdio>
#include <map>
#include <string>

using namespace std;

#define LEN_NAME 35
int main(void)
{
    char trash[2], treeName[LEN_NAME];
    int T, totalNumTree;
    map<string, int> mapNameToFreq;
    map<string, int>::iterator it;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    gets(trash);
    gets(trash);

    while(T)
    {
        mapNameToFreq.clear();
        totalNumTree = 0;

        while(gets(treeName) != NULL && treeName[0] != '\0')
        {
            string treeNameObj(treeName);

            it = mapNameToFreq.find(treeName);
            if(it == mapNameToFreq.end())
                mapNameToFreq[treeName] = 1;
            else
                it->second = it->second + 1;

            totalNumTree++;
        }

        for(it = mapNameToFreq.begin(); it != mapNameToFreq.end(); it++)
        {
            printf("%s %.4lf\n", it->first.c_str(), it->second * 100.0 / totalNumTree);
        }

        if(T != 1)
            printf("\n");
        T--;
    }
    return 0;
}
