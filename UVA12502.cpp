#include <cstdio>

using namespace std;

int main()
{
    int aDo, bDo, numTest, average, aBonus, cMoney, aDoForC, bDoForC;

    scanf("%d", &numTest);
    while(numTest)
    {
        scanf("%d %d %d", &aDo, &bDo, &cMoney);
        average = aDo + bDo;

        if(3 * aDo <= average)
            aBonus = 0;
        else
        {
            if(3 * bDo <= average)
                aBonus = cMoney;
            else
            {
                aDoForC = 3 * aDo - average;
                bDoForC = 3 * bDo - average;
                aBonus = aDoForC * cMoney / (aDoForC + bDoForC);
            }

        }

        printf("%d\n", aBonus);
        numTest--;
    }
    return 0;
}
