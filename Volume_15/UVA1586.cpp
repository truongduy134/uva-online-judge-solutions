/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

#include <cstdio>
#include <cctype>
#include <map>

#define MAX_LENGTH 80

using namespace std;

map<char, double> ATOMIC_WEIGHTS = {
  {'C', 12.01},
  {'H', 1.008},
  {'O', 16.0},
  {'N', 14.01}
};

double calcMolarMass(char formula[]) {
  int i = 0;
  double mass = 0, atomWeight;
  int atomCount = 0;

  while (formula[i]) {
    // Loop variant: formula[i] is always a character
    // representing a chemical element
    atomWeight = ATOMIC_WEIGHTS[formula[i]];

    atomCount = 0;
    i++;
    while (formula[i] && isdigit(formula[i])) {
      atomCount = atomCount * 10 + (formula[i] - '0');
      i++;
    }
    if (!atomCount) {
      atomCount = 1;
    }

    mass += atomWeight * atomCount;
  }

  return mass;
}

int main(void) {
  int numCases;
  char formula[MAX_LENGTH + 1];

  scanf("%d", &numCases);

  while (numCases) {
    scanf("%s", formula);

    printf("%.3lf\n", calcMolarMass(formula));

    numCases--;
  }
  return 0;
}
