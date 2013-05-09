#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_SIZE 2000
#define MAX_LEN 6000

int main(void)
{
    int T, P, numNeighbor[MAX_SIZE], countNum, minNum, flagFirst, numSpace;
    char trash[3], line[MAX_LEN];

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    scanf("%d", &T);

    while(T)
    {
        scanf("%d", &P);
        gets(trash);

        minNum = P;
        for(int i = 0; i < P; i++)
        {
            countNum = 0;

            gets(line);

            numSpace = 0;
            for(int k = 0; line[k] != '\0'; k++)
                if(line[k] == ' ')
                    numSpace++;

            numNeighbor[i] = numSpace + 1;

            if(numNeighbor[i] < minNum)
                minNum = numNeighbor[i];
        }

        flagFirst = 1;
        for(int i = 0; i < P; i++)
            if(numNeighbor[i] == minNum)
            {
                if(!flagFirst)
                    printf(" ");
                else
                    flagFirst = 0;

                printf("%d", i + 1);
            }
        printf("\n");

        T--;
    }
}
