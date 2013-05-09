#include <stdio.h>

int main()
{
    int input, divided, numOne, remainder;

    while(scanf("%d", &input) > 0)
    {
        divided = 1;
        numOne = 1;

        do
        {
            remainder = divided % input;
            if(remainder)
            {
                divided = remainder * 10 + 1;
                numOne++;
            }
        } while(remainder);

        printf("%d\n", numOne);
    }

    return 0;
}
