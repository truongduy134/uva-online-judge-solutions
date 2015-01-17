/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/* Methodology:
 * - Straightforward simulation problem.
 * - The checking if the game ends can be made simpler with encoding the
 *   game states as strings, and with using STL set or unordered_set
 */

#include <cstdio>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#define EMPTY 0
#define OCCUPIED 1
#define ADD_OP '+'

void encodeBoardState(
    const vector<vector<int> >& board, string& result) {
  int boardSize = board.size();
  result.clear();

  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardSize; ++j) {
      result.push_back('0' + board[i][j]);
    }
  }
}

void rotateClockwise90(vector<vector<int> >& board) {
  int boardSize = board.size();
  vector<vector<int> > temp(boardSize, vector<int>(boardSize, EMPTY));

  for (int r = 0; r < boardSize; ++r) {
    for (int c = 0; c < boardSize; ++c) {
      temp[c][boardSize - 1 - r] = board[r][c];
    }
  }
  board = temp;
}

bool checkLosingAndUpdateStateSet(
    const vector<vector<int> >& board,
    unordered_set<string>& losingStateSet) {
  vector<vector<int> > rotatedBoard(board);
  string encodedState;
  vector<string> newLosingStates;

  for (int i = 0; i < 4; ++i) {
    if (i) {
      rotateClockwise90(rotatedBoard);
    }
    encodeBoardState(rotatedBoard, encodedState);

    if (losingStateSet.find(encodedState) != losingStateSet.end()) {
      return true;
    } else {
      newLosingStates.push_back(encodedState);
    }
  }

  for (auto& newState : newLosingStates) {
    losingStateSet.insert(newState);
  }

  return false;
}

int main(void) {
  vector<vector<int> > board;
  unordered_set<string> losingStateSet;
  int boardSize;
  int r, c;
  char opSymbol[2];
  int numMove;
  bool gameOver;

  while (1) {
    scanf("%d", &boardSize);
    if (!boardSize) {
      break;
    }

    numMove = boardSize << 1;
    board.assign(boardSize, vector<int>(boardSize, EMPTY));
    losingStateSet.clear();
    gameOver = false;

    for (int move = 0; move < numMove; ++move) {
      scanf("%d %d %s", &r, &c, opSymbol);
      if (gameOver) {
        continue;
      }

      // Update game board state
      r--;
      c--;
      if (opSymbol[0] == ADD_OP) {
        board[r][c] = OCCUPIED;
      } else {
        board[r][c] = EMPTY;
      }

      if (checkLosingAndUpdateStateSet(board, losingStateSet)) {
        // Pattern is repeated. Other player wins
        gameOver = true;
        printf("Player %d wins on move %d\n", (1 - (move & 1)) + 1, move + 1);
      }
    }

    if (!gameOver) {
      printf("Draw\n");
    }
  }

  return 0;
}
