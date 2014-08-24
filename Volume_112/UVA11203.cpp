/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * This code contains C++ 11 syntax
 *
 * Methodology: A string is a ME theorem iff the following conditions are true:
 * - No invalid characters besides ?, M, E (case sensitive)
 * - There is exactly 1 M, and 1 E, and M occurs before E
 * - Let x, y, z be the number of ? before M, between M and E, and after E
 *   respectively. Then y >= 1, z > y and x = z - y
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SIZE 50

const vector<char> ME_ALPHABETS = {'M', 'E', '?'};

bool isMETheorem(const char * str) {
  if (!str) {
    return false;
  }

  for (int i = 0; str[i] != '\0'; ++i) {
    if (find(ME_ALPHABETS.begin(), ME_ALPHABETS.end(), str[i])
        == ME_ALPHABETS.end()) {
      return false;
    }
  }

  int mInd = -1, eInd = -1;
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == 'M') {
      if (mInd < 0) {
        mInd = i;
      } else { // There are two instances of M
        return false;
      }
    }

    if (str[i] == 'E') { 
      if (eInd < 0) {
        eInd = i;
      } else {
        return false;
      }
    }
  }
  if (mInd < 0 || eInd < 0 || mInd > eInd) {
    return false;
  }

  int numQBefore = 0, numQBetween = 0, numQAfter = 0;
  for (int i = 0; str[i] != '\0'; ++i) {
    if (str[i] == '?') {
      if (i < mInd) {
        numQBefore++;
      } else {
        if (i < eInd) {
          numQBetween++;
        } else {
          numQAfter++;
        }
      }
    }
  }

  return
    numQBetween >= 1 &&
    numQAfter > numQBetween &&
    numQBefore == numQAfter - numQBetween;  
}

int main(void) {
  int numTest;
  char str[MAX_SIZE + 1];

  scanf("%d", &numTest);
  while (numTest) {
    scanf("%s", str);

    printf(
      "%s\n",
      isMETheorem(str) ? "theorem" : "no-theorem");
    
    numTest--;
  }
  
  return 0;
}

