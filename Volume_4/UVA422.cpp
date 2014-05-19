/*******************************************************************************
 * Author: Nguyen Truong Duy
 *******************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>

const int MAX_SIZE = 100;

void reverseStr(const char source[], int wordLen, char dest[]) {
    for (int srcInd = wordLen - 1, destInd = 0; srcInd >= 0; --srcInd, ++destInd) {
        dest[destInd] = source[srcInd];
    }
    dest[wordLen] = '\0';
}

void swap(int & a, int & b) {
    int temp = a;
    a = b;
    b = temp;
}

bool findWordHorizontal(const char wordGrid[][MAX_SIZE + 1], int gridSize, const char word[], int wordLen, int startRow, int startCol) {
    if (startCol + wordLen > gridSize) {
        return false;
    }

    for (int i = 0; i < wordLen; i++) {
        if (wordGrid[startRow][startCol + i] != word[i]) {
            return false;
        }
    }

    return true;
}

bool findWordVertical(const char wordGrid[][MAX_SIZE + 1], int gridSize, const char word[], int wordLen, int startRow, int startCol) {
    if (startRow + wordLen > gridSize) {
        return false;
    }

    for (int i = 0; i < wordLen; i++) {
        if (wordGrid[startRow + i][startCol] != word[i]) {
            return false;
        }
    }

    return true;
}

bool findWordDiagonal(const char wordGrid[][MAX_SIZE + 1], int gridSize, const char word[], int wordLen, int startRow, int startCol) {
    if (startRow + wordLen > gridSize || startCol + wordLen > gridSize) {
        return false;
    }

    for (int i = 0; i < wordLen; i++) {
        if (wordGrid[startRow + i][startCol + i] != word[i]) {
            return false;
        }
    }

    return true;
}

bool findWordReverseDiagonal(const char wordGrid[][MAX_SIZE + 1], int gridSize, const char word[], int wordLen, int startRow, int startCol) {
    if (startRow - wordLen < 0 || startCol + wordLen > gridSize) {
        return false;
    }

    for (int i = 0; i < wordLen; i++) {
        if (wordGrid[startRow - i][startCol + i] != word[i]) {
            return false;
        }
    }

    return true;
}

bool findWordInGrid(const char wordGrid[][MAX_SIZE + 1], int gridSize, const char word[], int wordLen, int searchResult[]) {
    char cpyWord[MAX_SIZE + 1];
    strcpy(cpyWord, word);

    for (int turn = 0; turn < 2; turn++) {
        if (turn) {
            // Search reversed words
            reverseStr(word, wordLen, cpyWord);
        }

        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                searchResult[0] = row;
                searchResult[1] = col;

                bool found = true;

                if (findWordHorizontal(wordGrid, gridSize, cpyWord, wordLen, row, col)) {
                    searchResult[2] = row;
                    searchResult[3] = col + wordLen - 1;
                } else if (findWordVertical(wordGrid, gridSize, cpyWord, wordLen, row, col)) {
                    searchResult[2] = row + wordLen - 1;
                    searchResult[3] = col;
                } else if (findWordDiagonal(wordGrid, gridSize, cpyWord, wordLen, row, col)) {
                    searchResult[2] = row + wordLen - 1;
                    searchResult[3] = col + wordLen - 1;
                } else if (findWordReverseDiagonal(wordGrid, gridSize, cpyWord, wordLen, row, col)) {
                    searchResult[2] = row - wordLen + 1;
                    searchResult[3] = col + wordLen - 1;
                } else {
                    found = false;
                }

                if (found) {
                    if (turn) {
                        // Reversed turn
                        swap(searchResult[0], searchResult[2]);
                        swap(searchResult[1], searchResult[3]);
                    }
                    return true;
                }
            }
        }
    }

    return false;
}


int main(void) {
    char wordGrid[MAX_SIZE][MAX_SIZE + 1];
    char word[MAX_SIZE + 1];
    char gridSizeStr[MAX_SIZE + 1];
    int searchResult[4];

    scanf("%s", gridSizeStr);
    while (1) {
        int gridSize = atoi(gridSizeStr);
        if (!gridSize) {
            break;
        }

        // Read word grid
        for (int i = 0; i < gridSize; i++) {
            scanf("%s", wordGrid[i]);
        }

        // Read word
        while (1) {
            scanf("%s", word);
            if (!isalpha(word[0])) {
                strcpy(gridSizeStr, word);
                break;
            }

            if (findWordInGrid(wordGrid, gridSize, word, strlen(word), searchResult)) {
                printf("%d,%d %d,%d\n", searchResult[0] + 1, searchResult[1] + 1,
                    searchResult[2] + 1, searchResult[3] + 1);
            } else {
                printf("Not found\n");
            }
        }
    }

    return 0;
}
