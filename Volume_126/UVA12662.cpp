/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - This is a straightforward problem.
 */

#include <cstdio>
#include <vector>
#include <string>

using namespace std;

#define MAX_LEN 3

bool isKnown(const string& name) {
  return name.size() != 1 || name[0] != '?';
}

int minDistToKnownStudent(const vector<string>& names, int pos) {
  if (isKnown(names[pos])) {
    return 0;
  }

  int left = pos - 1;
  int right = pos + 1;

  while (left >= 0 && !isKnown(names[left])) {
    left--;
  }
  while (right < names.size() && !isKnown(names[right])) {
    right++;
  }

  int leftDist = pos - left;
  int rightDist = right - pos;
  if (left < 0) {
    return rightDist;
  }
  if (right >= names.size()) {
    return leftDist;
  }
  if (leftDist < rightDist) {
    return leftDist;
  }
  return rightDist;
}

int main(void) {
  int numStudents, numQueries, pos;
  vector<string> names;
  char cstr[MAX_LEN + 1];
  string printing;
  string relativePos;

  scanf("%d", &numStudents);

  for (int i = 0; i < numStudents; ++i) {
    scanf("%s", cstr);
    names.push_back(string(cstr));
  }

  scanf("%d", &numQueries);
  for (int i = 0; i < numQueries; ++i) {
    scanf("%d", &pos);
    pos--;

    int minDist = minDistToKnownStudent(names, pos);
    if (!minDist) {
      printf("%s\n", names[pos].c_str());
    } else {
      int left= pos - minDist;
      int right = pos + minDist;
      if (left >= 0 && right < numStudents &&
          isKnown(names[left]) && isKnown(names[right])) {
        printf(
          "middle of %s and %s\n",
          names[left].c_str(),
          names[right].c_str()
        );
      } else {
        int nearestInd = left;
        printing = "right of";
        if (right < numStudents && isKnown(names[right])) {
          nearestInd = right;
          printing = "left of";
        }
        relativePos = printing;
        minDist--;
        while (minDist) {
          relativePos += " " + printing;
          minDist--;
        }

        printf("%s %s\n", relativePos.c_str(), names[nearestInd].c_str());
      }
    }
  }

  return 0;
}
