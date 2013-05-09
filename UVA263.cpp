#include <cstdio>
#include <set>

using namespace std;

#define NUM_DIGIT 10
#define ASCENDING 1
#define DESCENDING 0

int getNumByArrangeDigit(int num, int direction);
void getDigitFrequency(int num, int digitFreq[]);

int main(void)
{
    set<int> setOfNum;
    bool stopFlg;
    int num, ascendNum, descendNum, chainLength;

    while(1)
    {
        setOfNum.clear();
        chainLength = 0;
        stopFlg = false;

        scanf("%d", &num);
        if(num == 0)
            break;

        printf("Original number was %d\n", num);

        while(!stopFlg)
        {
            ascendNum = getNumByArrangeDigit(num, ASCENDING);
            descendNum = getNumByArrangeDigit(num, DESCENDING);

            num = descendNum - ascendNum;
            if(setOfNum.find(num) == setOfNum.end())
                setOfNum.insert(num);
            else
                stopFlg = true;

            chainLength++;

            printf("%d - %d = %d\n", descendNum, ascendNum, num);
        }

        printf("Chain length %d\n\n", chainLength);
    }
    return 0;
}

int getNumByArrangeDigit(int num, int direction)
{
    int digitFreq[NUM_DIGIT], newNum = 0;

    getDigitFrequency(num, digitFreq);

    if(direction == ASCENDING)
    {
        for(int digit = 0; digit < NUM_DIGIT; digit++)
        {
            while(digitFreq[digit] > 0)
            {
                newNum = newNum * 10 + digit;
                digitFreq[digit]--;
            }
        }
    }
    else
    {
        for(int digit = NUM_DIGIT - 1; digit >= 0; digit--)
        {
            while(digitFreq[digit] > 0)
            {
                newNum = newNum * 10 + digit;
                digitFreq[digit]--;
            }
        }
    }

    return newNum;
}

void getDigitFrequency(int num, int digitFreq[])
{
    int digit;

    for(digit = 0; digit < NUM_DIGIT; digit++)
        digitFreq[digit] = 0;

    while(num)
    {
        digitFreq[num % 10]++;
        num /= 10;
    }
}
