#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

#define MAX_SIZE 105
#define MAX_DIRECTION 8
int vDirection[] = {0, 0, 1, -1, 1, -1, 1, -1},
    hDirection[] = {1, -1, 0, 0, 1, -1, -1, 1};

bool isValidCell(int r, int c, int numR, int numC)
{
    if(r < 0 || c < 0 || r >= numR || c >= numC)
        return false;
    return true;
}

int getSizeCluster(int sR, int sC, char sky[][MAX_SIZE], int numR, int numC)
{
    queue<pair<int, int> > queueBFS;
    queueBFS.push(make_pair(sR,sC));
    sky[sR][sC] = '.';

    pair<int, int> curCell;
    int nextR, nextC, sizeCluster = 0;

    while(!queueBFS.empty())
    {
        curCell = queueBFS.front();
        queueBFS.pop();

        sizeCluster++;

        for(int d = 0; d < MAX_DIRECTION; d++)
        {
            nextR = curCell.first + vDirection[d];
            nextC = curCell.second + hDirection[d];
            if(isValidCell(nextR, nextC, numR, numC) && sky[nextR][nextC] == '*')
            {
                queueBFS.push(make_pair(nextR, nextC));
                sky[nextR][nextC] = '.';
            }
        }
    }

    return sizeCluster;
}
int countStar(char sky[][MAX_SIZE], int numR, int numC)
{
    int numSizeCluster, numStar;

    numStar = 0;
    for(int r = 0; r < numR; r++)
        for(int c = 0; c < numC; c++)
            if(sky[r][c] == '*')
            {
                numSizeCluster = getSizeCluster(r, c, sky, numR, numC);
                if(numSizeCluster == 1)
                    numStar++;
            }

    return numStar;
}
int main(void)
{
    char sky[MAX_SIZE][MAX_SIZE], trash[10];
    int numR, numC;

  //  freopen("in.txt", "r", stdin);

    while(1)
    {
        scanf("%d %d", &numR, &numC);
        gets(trash);
        if(numR == 0 && numC == 0)
            break;

        for(int r = 0; r < numR; r++)
            gets(sky[r]);

        printf("%d\n", countStar(sky, numR, numC));
    }
    return 0;
}
