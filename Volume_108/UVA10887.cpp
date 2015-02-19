/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/**
 * Methodology:
 * - Use unordered set to store distinct strings in the concatenation language.
 *
 * - IMPORTANT: An empty string is valid in any language. Therefore, there are
 * empty lines in the input which should be treated as empty strings.
 */

#include <cstdio>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

#define MAX_LEN 10

int main(void) {
  vector<string> first, second;
  int numTests, caseId, numFirst, numSecond;
  char cstr[MAX_LEN + 1], trash[2];
  unordered_set<string> concatLang;

  scanf("%d", &numTests);
  caseId = 1;
  while (caseId <= numTests) {
    first.clear();
    second.clear();
    concatLang.clear();

    scanf("%d %d", &numFirst, &numSecond);
    gets(trash);

    for (int i = 0; i < numFirst; ++i) {
      gets(cstr);
      first.push_back(string(cstr));
    }
    for (int i = 0; i < numSecond; ++i) {
      gets(cstr);
      second.push_back(string(cstr));
    }

    // Construct the concatenation language
    for (int sndInd = 0; sndInd < numSecond; ++sndInd) {
      for (int fstInd = 0; fstInd < numFirst; ++fstInd) {
        concatLang.insert(first[fstInd] + second[sndInd]);
      }
    }

    printf("Case %d: %d\n", caseId, (int)concatLang.size());

    caseId++;
  }

  return 0;
}
