/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward problem.
 * - The methods string::find and
 *   string::replace(size_t pos, size_t len, const string& str) are useful.
 * - You must identify the correct number of characters to be replaced when
 *   calling string::replace
 */

#include <cstdio>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#define MAX_LEN 255

void applyEditRules(
    string& editText,
    const vector<pair<string, string> >& rules);

int main(void) {
  char word1[MAX_LEN + 1], word2[MAX_LEN + 1], trash[2];
  char editTextC[MAX_LEN + 1];
  vector<pair<string, string> > rules;
  int numRules;

  while (1) {
    scanf("%d", &numRules);
    gets(trash);
    if (!numRules) {
      break;
    }

    rules.clear();
    for (int i = 0; i < numRules; ++i) {
      gets(word1);
      gets(word2);
      rules.push_back(pair<string, string>(string(word1), string(word2)));
    }
    gets(editTextC);
    string editText(editTextC);

    applyEditRules(editText, rules);
    printf("%s\n", editText.c_str());
  }

  return 0;
}

void applyEditRules(
    string& editText,
    const vector<pair<string, string> >& rules) {
  int foundInd, replacedLen;
  for (int i = 0; i < rules.size(); ++i) {
    const pair<string, string>& rule = rules[i];
    replacedLen = rule.first.length();

    while ((foundInd = editText.find(rule.first)) != string::npos) {
      editText.replace(foundInd, replacedLen, rule.second);
    }
  }
}

