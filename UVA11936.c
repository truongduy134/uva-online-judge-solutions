#include <stdio.h>

int canFormTriangle(int a, int b, int c);

int main(void)
{
    int T, a, b, c;

    scanf("%d", &T);
    while(T)
    {
        scanf("%d %d %d", &a, &b, &c);
        if(canFormTriangle(a, b, c))
            printf("OK\n");
        else
            printf("Wrong!!\n");
        T--;
    }
    return 0;
}

int canFormTriangle(int a, int b, int c)
{
    if(a > b - c && b > a - c && a > c - b)
        return 1;
    return 0;
}
