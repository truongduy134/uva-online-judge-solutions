#include <stdio.h>
#include <string.h>

#define MAX_CHARACTER 256
#define MAX_LEN 800000

void prepareMapping(char mapEncodeToDecode[])
{
    char encodeToDecodeStr[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
    int i;

    for(i = 0; i < MAX_CHARACTER; i++)
        mapEncodeToDecode[i] = i;

    for(i = 1; encodeToDecodeStr[i] != '\0'; i++)
    {
        if(encodeToDecodeStr[i] == 'Q' || encodeToDecodeStr[i] == 'A' ||
           encodeToDecodeStr[i] == 'Z')
            continue;

        mapEncodeToDecode[(int) encodeToDecodeStr[i]] = encodeToDecodeStr[i - 1];
    }
}

void decode(char line[], char mapEncodeToDecode[])
{
    int i;

    for(i = 0; line[i] != '\0'; i++)
        line[i] = mapEncodeToDecode[(int) line[i]];
}

int main(void)
{
        char line[MAX_LEN];
        char mapEncodeToDecode[MAX_CHARACTER];

    /*    freopen("in.txt", "r", stdin); */

        prepareMapping(mapEncodeToDecode);

        while(gets(line) != NULL)
        {
            decode(line, mapEncodeToDecode);

            printf("%s\n", line);
        }
}
