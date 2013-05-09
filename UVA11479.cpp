#include <cstdio>

using namespace std;

bool isTriangle(int a, int b, int c)
{
    if(a <= 0 || b <= 0 || c  <= 0)
        return false;
    if(a <= c - b)
        return false;
    if(b <= a - c)
        return false;
    if(c <= b - a)
        return false;
    return true;
}

bool isEquilateral(int a, int b, int c)
{
    return (a == b) && (b == c);
}

bool isIsosceles(int a, int b, int c)
{
    return (a == b) || (a == c) || (b == c);
}

int main(void)
{
    int T, caseId, a, b, c;

  //  freopen("in.txt", "r", stdin);

    scanf("%d", &T);

    caseId = 1;
    while(caseId <= T)
    {
        scanf("%d %d %d", &a, &b, &c);

        printf("Case %d: ", caseId);

        if(!isTriangle(a, b, c))
            printf("Invalid\n");
        else
        {
            if(isEquilateral(a, b, c))
                printf("Equilateral\n");
            else
            {
                if(isIsosceles(a, b, c))
                    printf("Isosceles\n");
                else
                    printf("Scalene\n");
            }
        }

        caseId++;
    }
    return 0;
}
