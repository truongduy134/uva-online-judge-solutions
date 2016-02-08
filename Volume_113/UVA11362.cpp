/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

//// C++11 ////

/**
 * Methodology:
 * - Use Trie data structure for this problem
 * - First sort the list of phone numbers in the ascending order of their
 * string length
 * - Second, for each phone number in the sorted list, check if there is a
 * phone number in the Trie that is a prefix of this number. If there is, the
 * list is inconsistent. Otherwise, insert the current phone number into
 * the Trie
 *
 * - Time complexity: O(M * N) for each test case where M is the maximum length
 * of a word in the Trie (M = 10 in this problem), and N is the total number
 * of phone numbers
 */

#include <algorithm>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

using namespace std;

const int MAX_NUM_DIGITS = 10;
const int MAX_PHONE_NUMBER_LENGTH = 10;

struct DigitTrieNode {
  bool isEndOfWord;
  shared_ptr<DigitTrieNode> children[MAX_NUM_DIGITS];

  DigitTrieNode(): isEndOfWord(false), children() {}
};

class DigitTrie {

private:
  shared_ptr<DigitTrieNode> root;

public:
  DigitTrie() {
    this->root = make_shared<DigitTrieNode>();
  }

  void insert(const string& digitWord) {
    auto currentNode = this->root;

    for (auto ch : digitWord) {
      auto index = (int) (ch - '0');
      if (index < 0 || index >= MAX_NUM_DIGITS) {
        return;
      }

      if (!currentNode->children[index]) {
        currentNode->children[index] = make_shared<DigitTrieNode>();
      }
      currentNode = currentNode->children[index];
    }

    if (currentNode != this->root) {
      currentNode->isEndOfWord = true;
    }
  }

  string findPrefix(const string& digitWord) {
    string prefix;
    auto currentNode = this->root;

    for (auto ch : digitWord) {
      auto index = (int) (ch - '0');
      if (index < 0 ||
          index >= MAX_NUM_DIGITS ||
          !currentNode->children[index]) {
        currentNode = nullptr;
        break;
      }

      currentNode = currentNode->children[index];
      prefix.push_back(ch);
      if (currentNode->isEndOfWord) {
        break;
      }
    }

    if (currentNode && currentNode->isEndOfWord) {
      return prefix;
    }
    return "";
  }

};

int main(void) {
  int numCases;
  int numPhoneNumbers;
  char phoneNumberStr[MAX_PHONE_NUMBER_LENGTH + 1];

  scanf("%d", &numCases);
  for (auto i = 0; i < numCases; ++i) {
    scanf("%d", &numPhoneNumbers);

    DigitTrie phoneNumberTrie;
    vector<string> phoneNumbers;

    for (auto k = 0; k < numPhoneNumbers; ++k) {
      scanf("%s", phoneNumberStr);
      phoneNumbers.push_back(phoneNumberStr);
    }

    // Sort by length
    std::sort(
      phoneNumbers.begin(),
      phoneNumbers.end(),
      [](const string& phoneNumberA, const string& phoneNumberB) -> bool {
        return phoneNumberA.size() < phoneNumberB.size();
      }
    );

    bool isConsistent = true;
    for (const auto& phoneNumber : phoneNumbers) {
      if (isConsistent) {
        string prefixNumber = phoneNumberTrie.findPrefix(phoneNumber);
        if (prefixNumber.empty()) {
          phoneNumberTrie.insert(phoneNumber);
        } else {
          isConsistent = false;
        }
      }
    }

    printf("%s\n", isConsistent ? "YES" : "NO");
  }

  return 0;
}
