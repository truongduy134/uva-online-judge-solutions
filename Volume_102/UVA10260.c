#include <stdio.h>

#define NUM_ALPHA 26
#define MAX_LEN 200

const char mapAlphaToSoundex[NUM_ALPHA] = {'\0', '1', '2', '3',         /* A, B, C, D */
                                           '\0', '1', '2', '\0',        /* E, F, G, H */
                                           '\0', '2', '2', '4',         /* I, J, K, L */
                                           '5', '5', '\0', '1',         /* M, N, O, P */
                                           '2', '6', '2', '3',          /* Q, R, S, T */
                                           '\0', '1', '\0', '2',        /* U, V, W, X */
                                           '\0', '2'};                  /* Y, Z */

void convertToSoundex(char origin[], char soundex[])
{
    int originInd, newInd;
    char soundexLetter;
    bool flagJustWrite = true;

    for(originInd = 0, newInd = 0; origin[originInd] != '\0'; originInd++)
    {
        soundexLetter = mapAlphaToSoundex[origin[originInd] - 'A'];
        if(soundexLetter != '\0')
        {
            if(flagJustWrite || soundex[newInd - 1] != soundexLetter)
            {
                soundex[newInd] = soundexLetter;
                newInd++;
                flagJustWrite = false;
            }
        }
        else
            flagJustWrite = true;
    }

    soundex[newInd] = '\0';
}

int main(void)
{
    char origin[MAX_LEN + 1], soundex[MAX_LEN + 1];

 //   freopen("in.txt", "r", stdin);

    while(gets(origin) != NULL)
    {
        convertToSoundex(origin, soundex);

        printf("%s\n", soundex);
    }

    return 0;
}
