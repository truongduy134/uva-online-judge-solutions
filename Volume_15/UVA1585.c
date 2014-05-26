/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <stdio.h>

#define CORRECT 'O'
#define MAX_LEN 80

int calculateScore(char testResult[]) {
    int totalScore = 0;
    int numConsecutiveCorrect = 0;
    int i;

    for (i = 0; testResult[i] != '\0'; ++i) {
        if (testResult[i] == CORRECT) {
            numConsecutiveCorrect++;
            totalScore += numConsecutiveCorrect;
        } else {
            numConsecutiveCorrect = 0;
        }
    }

    return totalScore;
}

int main(void) {
    int numTest;
    char testResult[MAX_LEN + 1];

    scanf("%d", &numTest);
    while (numTest) {
        scanf("%s", testResult);

        printf("%d\n", calculateScore(testResult));

        numTest--;
    }

    return 0;
}
