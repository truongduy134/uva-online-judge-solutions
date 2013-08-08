/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 *  + Use brute-force approach.
 */

#include <stdio.h>
#include <math.h>

int isSquare(int N, int * ans);
int decomposeIntoSumThreeSquare(int N, int *A, int *B, int *C);

int main(void)
{
    int T, N, A, B, C;

    scanf("%d", &T);

    while(T)
    {
        scanf("%d", &N);

        if(decomposeIntoSumThreeSquare(N, &A, &B, &C))
            printf("%d %d %d\n", A, B, C);
        else
            printf("-1\n");

        T--;
    }
    return 0;
}

int decomposeIntoSumThreeSquare(int N, int *A, int *B, int *C)
{
    int a, b, c, squareA, squareB, squareC;

    for(a = 0; 3 * (squareA = a * a) <= N; a++)
        for(b = a; squareA + ((squareB = b * b) << 1) <= N; b++)
        {
            squareC = N - squareA - squareB;

            if(isSquare(squareC, &c) && c >= b)
            {
                *A = a;
                *B = b;
                *C = c;
                return 1;
            }
        }

    return 0;
}

int isSquare(int N, int * ans)
{
    int root = (int) floor(sqrt(N));

    if(root * root == N)
    {
        *ans = root;
        return 1;
    }

    return 0;
}
