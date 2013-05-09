#include <cstdio>
//#include <iostream>
using namespace std;

#define MAX_LEN 100
int main(void)
{
    char trash[MAX_LEN], direction[MAX_LEN];
    unsigned long long a, b, leftA, leftB, rightA, rightB, midA, midB;
    int T, i;

  //  freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    gets(trash);

    while(T)
    {
        gets(direction);

        leftA = 0;
        leftB = 1;
        rightA = 1;
        rightB = 0;
        i = 0;

        while(1)
        {
            midA = leftA + rightA;
            midB = leftB + rightB;

            if(direction[i] == '\0')
            {
                a = midA;
                b = midB;
                break;
            }

            if(direction[i] == 'L')
            {
                rightA = midA;
                rightB = midB;
            }
            else
            {
                leftA = midA;
                leftB = midB;
            }

            i++;
        }
        printf("%llu/%llu\n", a, b);
    //    cout << a << "/" << b << endl;
        T--;
    }
    return 0;
}
