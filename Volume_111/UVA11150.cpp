#include <cstdio>

using namespace std;

int main(void)
{
    int n, newB, old, totalDrink;

    while(scanf("%d", &n) > 0)
    {
        totalDrink = 0;
        newB = n;
        old = 0;
        do
        {
            newB += old / 3;     // Renew
            old = old % 3;
            totalDrink += newB;
            old += newB;
            newB = 0;
        } while(old > 2);

        if(old == 2)
            totalDrink += 1;

        printf("%d\n", totalDrink);
    }
    return 0;
}
