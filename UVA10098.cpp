#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_LEN 10

int main(void)
{
    int T, lenStr;
    char str[MAX_LEN + 1];

  //  freopen("in.txt", "r", stdin);

    scanf("%d", &T);

    while(T)
    {
        scanf("%s", str);
        lenStr = strlen(str);

        sort(str, str + lenStr);

        do
        {
            printf("%s\n", str);
        } while(next_permutation(str, str + lenStr));

        printf("\n");
        T--;
    }

    return 0;
}
