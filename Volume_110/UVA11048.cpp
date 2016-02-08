/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/**
 * Methodology:
 * - Because the length of each query word is short, we can use brute force
 * approach of each query word.
 * - For each query word not in the dictionary, we correct the misspelling
 * in a brute force manner (e.g. deleting every position of the word, inserting
 * to each position of the word every charater 'a' - 'z', swapping every
 * adjacent pairs of the word, etc.), and check if the new words are in the
 * dictionary. Then we obtain the list of all possible correct words, and choose
 * the word that appears earlier in the input if the list is non-empty
 */

#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAX_WORD_LENGTH = 25;

void fixMisspellingMissingChar(
  const string& word,
  const unordered_map<string, int>& dictionary,
  vector<string>& correctWords
) {
  string newWord(word);

  for (auto i = 0; i < word.size(); ++i) {
    for (auto c = 'a'; c <= 'z'; ++c) {
      newWord.insert(i, 1, c);

      auto dictionaryEntry = dictionary.find(newWord);
      if (dictionaryEntry != dictionary.end()) {
        correctWords.push_back(dictionaryEntry->first);
      }

      newWord.erase(i, 1);
    }
  }

  // Insert character at the end
  for (auto c = 'a'; c <= 'z'; ++c) {
    newWord.push_back(c);

    auto dictionaryEntry = dictionary.find(newWord);
    if (dictionaryEntry != dictionary.end()) {
      correctWords.push_back(dictionaryEntry->first);
    }

    newWord.pop_back();
  }
}

void fixMisspellingExtraChar(
  const string& word,
  const unordered_map<string, int>& dictionary,
  vector<string>& correctWords
) {
  for (auto i = 0; i < word.size(); ++i) {
    string newWord(word);
    newWord.erase(i, 1);

    auto dictionaryEntry = dictionary.find(newWord);
    if (dictionaryEntry != dictionary.end()) {
      correctWords.push_back(dictionaryEntry->first);
    }
  }
}

void fixMisspellingWrongChar(
  const string& word,
  const unordered_map<string, int>& dictionary,
  vector<string>& correctWords
) {
  string newWord(word);

  for (auto i = 0; i < word.size(); ++i) {
    auto originalChar = newWord[i];

    for (auto c = 'a'; c <= 'z'; ++c) {
      if (c != originalChar) {
        newWord[i] = c;
      }
      auto dictionaryEntry = dictionary.find(newWord);
      if (dictionaryEntry != dictionary.end()) {
        correctWords.push_back(dictionaryEntry->first);
      }
    }

    newWord[i] = originalChar;
  }
}

void swapChars(string& str, int i, int j) {
  auto c = str[i];
  str[i] = str[j];
  str[j] = c;
}

void fixMisspellingSwappingChar(
  const string& word,
  const unordered_map<string, int>& dictionary,
  vector<string>& correctWords
) {
  string newWord(word);

  for (auto i = 0; i < word.size() - 1; ++i) {
    swapChars(newWord, i, i + 1);

    auto dictionaryEntry = dictionary.find(newWord);
    if (dictionaryEntry != dictionary.end()) {
      correctWords.push_back(dictionaryEntry->first);
    }

    swapChars(newWord, i, i + 1);
  }
}

void fixMisspelling(
  const string& word,
  const unordered_map<string, int>& dictionary,
  vector<string>& correctWords
) {
  fixMisspellingMissingChar(word, dictionary, correctWords);
  fixMisspellingExtraChar(word, dictionary, correctWords);
  fixMisspellingWrongChar(word, dictionary, correctWords);
  fixMisspellingSwappingChar(word, dictionary, correctWords);
}

int main(void) {
  char word[MAX_WORD_LENGTH + 1];
  int numWords, numQuery;
  unordered_map<string, int> dictionary;

  scanf("%d", &numWords);
  for (auto i = 0; i < numWords; i++) {
    scanf("%s", word);
    dictionary[word] = i;
  }

  scanf("%d", &numQuery);
  for (auto i = 0; i < numQuery; ++i) {
    scanf("%s", word);

    if (dictionary.find(word) != dictionary.end()) {
      printf("%s is correct\n", word);
    } else {
      vector<string> correctWords;

      fixMisspelling(word, dictionary, correctWords);

      if (correctWords.empty()) {
        printf("%s is unknown\n", word);
      } else {
        int displayWordIndex;
        int minDictIndex = numWords;
        for (auto i = 0; i < correctWords.size(); ++i) {
          auto dictIndex = dictionary[correctWords[i]];
          if (dictIndex < minDictIndex) {
            minDictIndex = dictIndex;
            displayWordIndex = i;
          }
        }
        printf(
          "%s is a misspelling of %s\n",
          word,
          correctWords[displayWordIndex].c_str()
        );
      }
    }
  }

  return 0;
}
