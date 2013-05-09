#include <cstdio>

using namespace std;

#define MAX_SIZE 100
#define MAX_LEN_INPUT 100010
#define MAX_LEN 3

char incrementHexa(char hexa)
{
    if(hexa == '9')
        return 'A';
    if(hexa == 'F')
        return '0';
    return hexa + 1;
}

char decrementHexa(char hexa)
{
    if(hexa == 'A')
        return '9';
    if(hexa == '0')
        return 'F';
    return hexa - 1;
}

void increment(char byteHexa[])
{
    int flagMoreAdd = 0;
    if(byteHexa[1] == 'F')
        flagMoreAdd = 1;
    byteHexa[1] = incrementHexa(byteHexa[1]);
    if(flagMoreAdd)
        byteHexa[0] = incrementHexa(byteHexa[0]);
}

void decrement(char byteHexa[])
{
    int flagMoreSub = 0;
    if(byteHexa[1] == '0')
        flagMoreSub = 1;
    byteHexa[1] = decrementHexa(byteHexa[1]);
    if(flagMoreSub)
        byteHexa[0] = decrementHexa(byteHexa[0]);
}

int main(void)
{
    char memory[MAX_SIZE][MAX_LEN], trash[MAX_LEN], cmd[MAX_LEN_INPUT];
    int memPos, caseId, T;

 //   freopen("in.txt", "r", stdin);
 //   freopen("out.txt", "w", stdout);

    scanf("%d", &T);
    gets(trash);
    caseId = 1;
    while(T)
    {
        gets(cmd);

        // Initialize the memory
        for(int i = 0; i < MAX_SIZE; i++)
        {
            memory[i][0] = memory[i][1] = '0';
            memory[i][2] = '\0';
        }

        memPos = 0;
        for(int i = 0; cmd[i] != '\0'; i++)
        {
            switch(cmd[i])
            {
                case '>':
                    memPos++;
                    if(memPos >= MAX_SIZE)
                        memPos = 0;
                    break;
                case '<':
                    memPos--;
                    if(memPos < 0)
                        memPos = MAX_SIZE - 1;
                    break;
                case '+':
                    increment(memory[memPos]);
                    break;
                case '-':
                    decrement(memory[memPos]);
                    break;
            }
        }

        printf("Case %d:", caseId);
        for(int i = 0; i < MAX_SIZE; i++)
            printf(" %s", memory[i]);
        printf("\n");
        T--;
        caseId++;
    }
    return 0;
}
