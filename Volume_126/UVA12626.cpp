/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

/* Methodology:
 *  + For each input string S, compute an array A such that A[x] is the frequency
 *      of character x in S (x = 'A', 'B', ..., 'Z')
 *  + The word MARGARITA has 1 M, 3 A, 2 R, 1 G, 1 I, and 1 T
 *  + So the number of pizzas that can be made with the string S is equal to
 *      min{A['M'], A['A'] / 3, A['R'] / 2, A['G'], A['I'], A['T']}
 *
 *  + Time complexity: O(L) where L is length of input strings
 */

#include <cstdio>
#include <map>

using namespace std;

const int NUM_ALPHA_CHARACTER = 26;
const char FOOD_STR[] = "MARGARITA";
const int MAX_STR_LENGTH = 600;

map<char, int> mapCharToRequiredFreq;

void preprocessMap() {
    for (int i = 0; FOOD_STR[i] != '\0'; ++i) {
        if (mapCharToRequiredFreq.find(FOOD_STR[i]) == mapCharToRequiredFreq.end()) {
            mapCharToRequiredFreq[FOOD_STR[i]] = 1;
        } else {
            mapCharToRequiredFreq[FOOD_STR[i]]++;
        }
    }
}

void countCharFrequency(const char word[], int freqTable[]) {
    // Assume word contains only A - Z characters

    for (int i = 0; i < NUM_ALPHA_CHARACTER; ++i) {
        freqTable[i] = 0;
    }
    for (int i = 0; word[i] != '\0'; ++i) {
        freqTable[(int) (word[i] - 'A')]++;
    }
}

int countNumPizzaMade(const char word[]) {
    int freqTable[NUM_ALPHA_CHARACTER] = {0};

    countCharFrequency(word, freqTable);

    int numPizza = -1;
    for (map<char, int>::iterator it = mapCharToRequiredFreq.begin();
            it != mapCharToRequiredFreq.end(); ++it) {
        char alpha = it->first;
        int requiredQuantity = it->second;
        int ratio = freqTable[(int) (alpha - 'A')] / requiredQuantity;
        if (numPizza < 0 || ratio < numPizza) {
            numPizza = ratio;
            if (!numPizza) {
                break;
            }
        }
    }

    return numPizza;
}

int main(void) {
    int numTest;
    char word[MAX_STR_LENGTH + 1];

    preprocessMap();

    scanf("%d", &numTest);
    while(numTest) {
        scanf("%s", word);

        printf("%d\n", countNumPizzaMade(word));

        numTest--;
    }

    return 0;
}
