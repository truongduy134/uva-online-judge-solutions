#include <cstdio>
#include <cstdlib>
#include <cctype>

using namespace std;

#define MAX_LEN 50

int convertHexaToDecimal(char digit[])
{
    int num = 0;
    for(int i = 0; digit[i] != '\0'; i++)
    {
        num = num * 16;
        if(isdigit(digit[i]))
            num += (digit[i] - '0');
        else
            num += (toupper(digit[i]) - 'A' + 10);
    }

    return num;
}

void convertDecimalToHexa(int dec, char output[])
{
    char tempArr[MAX_LEN];
    int numDigit = 0, r;

    if(dec == 0)
    {
        output[0] = '0';
        output[1] = '\0';
        return;
    }

    while(dec)
    {
        r = dec % 16;
        dec /=  16;
        if(r <= 9)
            tempArr[numDigit] = '0' + r;
        else
            tempArr[numDigit] = 'A' + r - 10;
        numDigit++;
    }

    for(int i = 0; i < numDigit; i++)
        output[i] = tempArr[numDigit - 1 - i];
    output[numDigit] = '\0';
}
int main(void)
{
    char line[MAX_LEN], hexaArr[MAX_LEN];
    int inDecimal;

   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);

    while(1)
    {
        gets(line);

        if(line[1] == 'x')
        {
            // Input is hexadecimal
            printf("%d\n", convertHexaToDecimal(line + 2));
        }
        else
        {
            inDecimal = atoi(line);
            if(inDecimal < 0)
                break;
            convertDecimalToHexa(inDecimal, hexaArr);
            printf("0x%s\n", hexaArr);
        }
    }
    return 0;
}
