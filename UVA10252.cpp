#include <cstdio>

#define NUM_CHAR 30
#define MAX_LEN 1500
int main(void)
{
    char result[MAX_LEN], strA[MAX_LEN], strB[MAX_LEN];
    int lenR, sieveA[NUM_CHAR], sieveR[NUM_CHAR];

   // freopen("in.txt", "r", stdin);

    while(gets(strA) != NULL)
    {
        gets(strB);

        for(int i = 0; i < NUM_CHAR; i++)
        {
            sieveA[i] = sieveR[i] = 0;
        }

        for(int i = 0; strA[i] != '\0'; i++)
            sieveA[strA[i] - 'a']++;

        for(int i = 0; strB[i] != '\0'; i++)
            if(sieveA[strB[i] - 'a'] > 0)
            {
                sieveR[strB[i] - 'a']++;
                sieveA[strB[i] - 'a']--;
            }

        lenR = 0;
        for(int i = 0; i < NUM_CHAR; i++)
        {
            while(sieveR[i]) {
                result[lenR++] = i + 'a';
                sieveR[i]--;
            }
        }

        result[lenR] = '\0';
        printf("%s\n", result);
    }
    return 0;
}
