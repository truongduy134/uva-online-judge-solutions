#include <stdio.h>

#define MAX_DEGREE 8

typedef struct {
    int coeff[MAX_DEGREE + 1];
} Polynomial;

void printTerm(int coeff, int degree)
{
    if(coeff == 0)
        return;

    if(coeff != 1 || degree == 0)
        printf("%d", coeff);

    if(degree == 0)
        return;

    if(degree != 1)
        printf("x^%d", degree);
    else
        printf("x");
}

void printPolynomial(Polynomial *poly)
{
    int firstTerm = 1, degree, coeff, allZeroFlg = 1;

    for(degree = MAX_DEGREE; degree >= 0; degree--)
    {
        coeff = poly->coeff[degree];

        if(coeff != 0)
        {
            allZeroFlg = 0;
            if(firstTerm)
            {
                if(coeff == -1)
                {
                    printf("-");
                    coeff = -coeff;
                }

                printTerm(coeff, degree);
                firstTerm = 0;
            }
            else
            {
                if(coeff < 0)
                {
                    printf(" - ");
                    coeff = -coeff;
                }
                else
                    printf(" + ");
                printTerm(coeff, degree);
            }
        }
    }

    if(allZeroFlg)
        printf("0");
}

int main(void)
{
    Polynomial poly;
    int endInput = 0, degree, coeff;

    while(1)
    {
        for(degree = MAX_DEGREE; degree >= 0; degree--)
            if(scanf("%d", &coeff) > 0)
            {
                poly.coeff[degree] = coeff;
            }
            else
            {
                endInput = 1;
                break;
            }

        if(endInput)
            break;

        printPolynomial(&poly);
        printf("\n");
    }

    return 0;
}
