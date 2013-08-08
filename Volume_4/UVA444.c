#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

void decode(char input[], char output[]);
void encode(char input[], char output[]);

int main(void)
{
    char input[MAX_LEN + 1], output[MAX_LEN + 1];

 /*   freopen("in.txt", "r", stdin); */

    while(gets(input) != NULL)
    {
        if(isdigit(input[0]))
            decode(input, output);
        else
            encode(input, output);

        printf("%s\n", output);
    }

    return 0;
}

void encode(char input[], char output[])
{
    int indOut, indIn, ascii;

    indOut = 0;
    for(indIn = (int) strlen(input) - 1; indIn >= 0; indIn--)
    {
        ascii = (int) input[indIn];

        while(ascii)
        {
            output[indOut] = (char) (ascii % 10 + '0');
            indOut++;
            ascii /= 10;
        }
    }

    output[indOut] = '\0';
}

void decode(char input[], char output[])
{
    int indIn, indOut, ascii, time, numDigit;

    indOut = 0;
    for(indIn = (int) strlen(input) - 1; indIn >= 0;)
    {
        ascii = 0;
        if(input[indIn] == '1')
            numDigit = 3;
        else
            numDigit = 2;
        for(time = 0; time < numDigit; time++)
        {
            ascii = 10 * ascii + (input[indIn] - '0');
            indIn--;
        }

        output[indOut] = (char) ascii;
        indOut++;
    }

    output[indOut] = '\0';
}

