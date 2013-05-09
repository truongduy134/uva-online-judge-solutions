#include <cstdio>

using namespace std;

#define LEN_LINE 100001
#define MAX_SIZE 35

int main(void)
{
    char flag, line[LEN_LINE], digitArr[MAX_SIZE];
    int num, index, blockSize, numBit;
    bool endNum;

  //  freopen("in.txt", "r", stdin);
  //  freopen("out.txt", "w", stdout);

    numBit = 0;
    num = 0;
    while(1)
    {
        gets(line);
        if(line[0] == '~')
            break;

        index = 0;
        blockSize = 0;

        for(index = 0; ;index++)
        {
            if(line[index] == '0')
            {
                blockSize++;
                continue;
            }

            if(line[index] == '#')
            {
                endNum = true;
                break;
            }

            if(line[index] == ' ' || line[index] == '\0')
            {
                if(blockSize == 1)
                    flag = '1';
                else
                {
                    if(blockSize == 2)
                        flag = '0';
                    else
                        if(blockSize > 2)
                        {
                            for(int i = 1; i <= blockSize - 2; i++)
                            {
                                digitArr[numBit] = flag;
                                numBit++;
                            }
                        }
                }

                blockSize = 0;
                if(line[index] == '\0')
                    break;
            }
        }

        if(endNum)
        {
           // digitArr[numBit] = '\0';
           // puts(digitArr);
            for(int i = numBit - 1; i >= 0; i--)
                if(digitArr[i] == '1')
                    num |= (1 << (numBit - 1 - i));

            printf("%d\n", num);

            endNum = false;
            numBit = 0;
            num = 0;
        }
    }
    return 0;
}
