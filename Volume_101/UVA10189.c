/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <stdio.h>

#define MAX_SIZE 100
#define MINE '*'

void fillMineInfo(char mineField[][MAX_SIZE + 1], int numR, int numC);
int countNeighborMines(char mineField[][MAX_SIZE + 1], int numR, int numC,
  int curR, int curC);

int main(void) {
  char mineField[MAX_SIZE][MAX_SIZE + 1];
  char trash[2];
  int numR, numC, r;
  int caseId = 1;

  while (1) {
    scanf("%d %d", &numR, &numC);
    if (!(numR && numC)) {
      break;
    }
    gets(trash);

    for (r = 0; r < numR; ++r) {
      gets(mineField[r]);
    }

    fillMineInfo(mineField, numR, numC);

    if (caseId > 1) {
      printf("\n");
    }
    printf("Field #%d:\n", caseId);
    for (r = 0; r < numR; ++r) {
      puts(mineField[r]);
    }

    caseId++;
  }

  return 0;
}

void fillMineInfo(char mineField[][MAX_SIZE + 1], int numR, int numC) {
  int r, c;

  for (r = 0; r < numR; ++r) {
    for (c = 0; c < numC; ++c) {
      if (mineField[r][c] != MINE) {
        mineField[r][c] =
          '0' + countNeighborMines(mineField, numR, numC, r, c);
      }
    }
  }
}

int countNeighborMines(
    char mineField[][MAX_SIZE + 1],
    int numR, int numC,
    int curR, int curC) {
  int offsetR, offsetC, newR, newC;
  int count = 0;

  for (offsetR = -1; offsetR <= 1; ++offsetR) {
    for (offsetC = -1; offsetC <= 1; ++offsetC) {
      newR = curR + offsetR;
      newC = curC + offsetC;
      if (newR >= 0 && newC >= 0 && newR < numR && newC < numC &&
          mineField[newR][newC] == MINE) {
        count++;
      }
    }
  }

  return count;
}

