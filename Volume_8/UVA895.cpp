/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Methodology:
 * - For each word in the dictionary, generate its histogram.
 * - Let the list of histograms be H
 * - Treat the puzzle as a string of characters (without whitespaces, and
 *   generate the histogram (call it PH)
 * - We count the number of histogram H[i] in H such that it is contained
 *   in the histogram PH. That number equals to the number of words in
 *   the dictionary that can be formed by the puzzle.
 */

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define END_SECTION_CHAR '#'
#define MAX_SIZE 20
#define ALPHABET_SIZE 26

void getWordHistogram(
    vector<int>& histogram,
    const string& word) {
  histogram.assign(ALPHABET_SIZE, 0);
  for (int i = 0; i < word.size(); ++i) {
    histogram[word[i] - 'a']++;
  }
}

// Check if histogram 1 is a subset of histogram 2
bool isSubsetHistogram(
    const vector<int>& histogram1,
    const vector<int>& histogram2) {
  for (int i = 0; i < ALPHABET_SIZE; ++i) {
    if (histogram1[i] > histogram2[i]) {
      return false;
    }
  }
  return true;
}

int main(void) {
  char str[MAX_SIZE + 1];
  vector<string> words;
  vector<vector<int> > histograms;

  while (1) {
    scanf("%s", str);
    if (str[0] == END_SECTION_CHAR) {
      break;
    }
    words.push_back(str);
  }  

  for (int i = 0; i < words.size(); ++i) {
    vector<int> wordHistogram;
    getWordHistogram(wordHistogram, words[i]);
    histograms.push_back(wordHistogram);
  }

  vector<int> puzzleHistogram;
  
  gets(str);
  while (1) {
    gets(str);
    if (str[0] == END_SECTION_CHAR) {
      break;
    }

    string puzzle(str);
    puzzle.erase(
      remove(puzzle.begin(), puzzle.end(), ' '),
      puzzle.end());

    getWordHistogram(puzzleHistogram, puzzle);
    int wordCount = 0;
    for (int i = 0; i < words.size(); ++i) {
      if (isSubsetHistogram(histograms[i], puzzleHistogram)) {
        wordCount++;
      }
    }
    printf("%d\n", wordCount);  
  }
     
  return 0;
}

