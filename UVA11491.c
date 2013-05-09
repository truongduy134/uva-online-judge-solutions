#include <stdio.h>
#include <string.h>

#define NUM_DIGIT 10
#define MAX_LEN 100010

void getLargestNumAfterRemoveDigit(char digitStr[], int numDigitPresent, int numDigitRemove, char resultDigitStr[]);

int main(void)
{
    int numDigitPresent, numDigitRemove;
    char digitStr[MAX_LEN + 1], resultDigitStr[MAX_LEN + 1];

    while(1)
    {
        scanf("%d %d", &numDigitPresent, &numDigitRemove);
        if(numDigitPresent == 0 && numDigitRemove == 0)
            break;

        scanf("%s", digitStr);

        getLargestNumAfterRemoveDigit(digitStr, numDigitPresent, numDigitRemove, resultDigitStr);

        printf("%s\n", resultDigitStr);
    }

    return 0;
}

/* Methodology: Use greedy approach
 *      + The result string will have lenResult = numDigitPresent - numDigitRemove digits
 *      + Consider the i-th digit of the original string.
 *      + If numDigitRemove == 0, push this digit to the stack.
 *      + While numDigitRemove > 0 and this digit is larger than the top of the stack, pop the top of the stack.
 *      + Push this digit to the stack.
 *      + Move to the next digit.
 *      + In the end, take only lenResult digits from the bottom of the stack
 */
void getLargestNumAfterRemoveDigit(char digitStr[], int numDigitPresent, int numDigitRemove, char resultDigitStr[])
{
    int ind, lenResult, stackSize;

    lenResult = numDigitPresent - numDigitRemove;

    if(numDigitRemove == 0)
    {
        strcpy(resultDigitStr, digitStr);
        return;
    }

    if(numDigitRemove >= numDigitPresent)
    {
        resultDigitStr[0] = '0';
        resultDigitStr[1] = '\0';
        return;
    }

    stackSize = 0;
    for(ind = 0; digitStr[ind] != '\0'; ind++)
    {
        while(numDigitRemove > 0 && stackSize > 0 && digitStr[ind] > resultDigitStr[stackSize - 1])
        {
            stackSize--;
            numDigitRemove--;
        }

        resultDigitStr[stackSize] = digitStr[ind];
        stackSize++;
    }

    /* Take only lenResult = numDigitPresent - numDigitRemove digits from the bottom of the stack */
    resultDigitStr[lenResult] = '\0';
}
