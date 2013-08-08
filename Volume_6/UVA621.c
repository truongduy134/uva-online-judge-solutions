/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <stdio.h>
#include <string.h>

const int MAX_LEN = 1000;

enum RESULT_TYPE {
    POSITIVE = 0,
    NEGATIVE = 1,
    FAIL = 2,
    INCOMPLETE = 3
};
const char OUTPUT_SYMBOL[] = "+-*?";

enum RESULT_TYPE getExperimentResult(char str[]);

int main(void)
{
        int T;
        char str[MAX_LEN + 1];

        scanf("%d", &T);

        while(T)
        {
            scanf("%s", str);

            printf("%c\n", OUTPUT_SYMBOL[(int) getExperimentResult(str)]);
            T--;
        }
        return 0;
}

enum RESULT_TYPE getExperimentResult(char str[])
{
    int len = (int) strlen(str);

    if(len < 3)
    {
        if(str[0] == '1' || str[0] == '4')
            return POSITIVE;
        if(len == 2 && str[0] == '7' && str[1] == '8')
            return POSITIVE;
    }

    if(str[len - 2] == '3' && str[len - 1] == '5')
        return NEGATIVE;
    if(str[0] == '9' && str[len - 1] == '4')
        return FAIL;
    return INCOMPLETE;
};
