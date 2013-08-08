#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 7
#define MAX_LEN_INPUT 1000

int convertToDecimal(char representation[], int base);
int convertDecimalToBase(int decimal, char result[], int targetBase);
void reverseStr(char str[]);

int main(void)
{
    char representation[MAX_LEN_INPUT + 1], result[MAX_LEN + 1];
    int fromBase, toBase, decimal;

    while(scanf("%s", representation) > 0)
    {
        scanf("%d %d", &fromBase, &toBase);

        decimal = convertToDecimal(representation, fromBase);
        if(decimal < 0 || convertDecimalToBase(decimal, result, toBase) < 0)
            printf("%7s\n", "ERROR");
        else
            printf("%7s\n", result);

    }
    return 0;
}

int convertToDecimal(char representation[], int base)
{
    int len = strlen(representation);
    int decVal = 0, i, digitVal;
    if(len > MAX_LEN)
        return -1;

    for(i = 0; representation[i] != '\0'; i++)
    {
        if(isdigit(representation[i]))
            digitVal = representation[i] - '0';
        else
            digitVal = representation[i] - 'A' + 10;

        decVal = decVal * base + digitVal;
    }

    return decVal;
}

int convertDecimalToBase(int decimal, char result[], int targetBase)
{
    int ind = 0, temp;

    if(decimal == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return 0;
    }

    while(ind < MAX_LEN && decimal)
    {
        temp = decimal % targetBase;
        if(temp < 10)
            result[ind] = (char) (temp + '0');
        else
            result[ind] = (char) (temp - 10 + 'A');

        decimal /= targetBase;
        ind++;
    }

    if(decimal)
        return -1;

    result[ind] = '\0';
    reverseStr(result);

    return 0;
}

void reverseStr(char str[])
{
    int len = (int) strlen(str);
    int left = 0, right = len - 1;
    char temp;

    while(left < right)
    {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;

        left++;
        right--;
    }
}
