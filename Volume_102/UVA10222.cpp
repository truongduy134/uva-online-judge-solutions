/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Following are the assumptions we can make to pass the test cases:
 *  - All alpha-characters are lowercase
 *  - No 'shift-characters' are present (such as !, @, {, }, ?)
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#define MAX_LEN 10000

using namespace std;

char decodeCharacter(char character, const vector<string>& keyboard) {
  for (int i = 0; i < keyboard.size(); ++i) {
    int charInd = keyboard[i].find(character);
    if (charInd != string::npos && charInd >= 2) {
      return keyboard[i][charInd - 2];
    }
  }
  return character;
}

int main(void) {
  vector<string> keyboard;
  keyboard.push_back("1234567890-=");
  keyboard.push_back("qwertyuiop[]\\");
  keyboard.push_back("asdfghjkl;'");
  keyboard.push_back("zxcvbnm,./");

  char encodedStr[MAX_LEN + 1];
  gets(encodedStr);
  
  char decodedStr[MAX_LEN + 1];
  int len = 0;
  for (len = 0; encodedStr[len] != '\0'; ++len) {
    decodedStr[len] = decodeCharacter(encodedStr[len], keyboard);
  }
  decodedStr[len] = '\0';
  printf("%s\n", decodedStr);
       
  return 0;
}
