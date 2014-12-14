/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward problem.
 * - Note that if a word has length < 2, it is not a cool word
 * - For a word that has length >= 2, compute the list of integers indicating
 * the frequencies of distinct characters ('a' to 'z') in a word, then check
 * if all those integers are distinct.
 */

#include <cstdio>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEN 30
#define NUM_ALPHABET 26

int countCoolWords(const vector<string>& words);
bool isCoolWord(const string& word);
bool hasDuplicates(const vector<int>& arr);
void getFrequencies(const string& word, vector<int>& charFrequency);

int main(void) {
  int numWords;
  int caseId = 1;
  char word[MAX_LEN + 1];
  vector<string> words;

  while (scanf("%d", &numWords) > 0) {
    words.clear();

    for (int i = 0; i < numWords; ++i) {
      scanf("%s", word);
      words.push_back(word);
    }

    printf("Case %d: %d\n", caseId, countCoolWords(words));
    caseId++;
  }

  return 0;
}

int countCoolWords(const vector<string>& words) {
  int count = 0;
  for (int i = 0; i < words.size(); ++i) {
    if (isCoolWord(words[i])) {
      count++;
    }
  }
  return count;
}

bool isCoolWord(const string& word) {
  if (word.size() < 2) {
    return false;
  }
  vector<int> charFrequency;
  getFrequencies(word, charFrequency);
  return !hasDuplicates(charFrequency);
}

void getFrequencies(const string& word, vector<int>& charFrequency) {
  vector<int> histogram(NUM_ALPHABET, 0);
  charFrequency.clear();

  for (int i = 0; i < word.size(); ++i) {
    histogram[(int)(word[i] - 'a')]++;
  }

  for (int i = 0; i < NUM_ALPHABET; ++i) {
    if (histogram[i]) {
      charFrequency.push_back(histogram[i]);
    }
  }
}

bool hasDuplicates(const vector<int>& arr) {
  set<int> mSet;
  for (int i = 0; i < arr.size(); ++i) {
    int oldSize = mSet.size();
    mSet.insert(arr[i]);
    if (mSet.size() == oldSize) {
      return true;
    }
  }
  return false;
}
