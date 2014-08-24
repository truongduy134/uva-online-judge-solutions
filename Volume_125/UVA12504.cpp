/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <map>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#define MAX_LINE_SIZE 100
#define NUM_COMPARE_FIELD 3
#define ADD_CHAR '+'
#define DELETE_CHAR '-'
#define MODIFY_CHAR '*'

const int COMPARE_FIELD[] = {ADD_CHAR, DELETE_CHAR, MODIFY_CHAR};

void stringToDict(char * str, map<string, string>& dict) {
  dict.clear();

  if (!str) {
    return;
  }

  const static char delimiter[] = "{,:}";

  vector<string> tokenList;  
  char * token = strtok(str, delimiter);
  while (token) {
    tokenList.push_back(token);
    token = strtok(NULL, delimiter);
  }

  for (int i = 0; i < tokenList.size(); i += 2) {
    dict[tokenList[i]] = tokenList[i + 1];
  }
}

bool compareDicts(
    const map<string, string>& newDict,
    const map<string, string>& oldDict,
    map<char, vector<string> >& compareResult) {
  
  for (int i = 0; i < NUM_COMPARE_FIELD; ++i) {
    compareResult[COMPARE_FIELD[i]] = vector<string>();
  }

  map<string, string>::const_iterator it;
  for (it = newDict.begin(); it != newDict.end(); ++it) {
    map<string, string>::const_iterator oldIt = oldDict.find(it->first);
    if (oldIt == oldDict.end()) {
      compareResult[ADD_CHAR].push_back(it->first);
    } else {
      if (oldIt->second != it->second) {
        compareResult[MODIFY_CHAR].push_back(it->first);
      }
    }
  }
  for (it = oldDict.begin(); it != oldDict.end(); ++it) {
    if (newDict.find(it->first) == newDict.end()) {
      compareResult[DELETE_CHAR].push_back(it->first);
    }
  }

  bool hasChanges = false;
  for (int i = 0; i < NUM_COMPARE_FIELD; ++i) {
    hasChanges |= !compareResult[COMPARE_FIELD[i]].empty();
  }

  return hasChanges;
}

int main(void) {
  int numTest;
  char oldLine[MAX_LINE_SIZE + 1];
  char newLine[MAX_LINE_SIZE + 1];
  map<string, string> newDict, oldDict;
  map<char, vector<string> > compareResult;

  scanf("%d", &numTest);

  while (numTest) {
    scanf("%s", oldLine);
    scanf("%s", newLine);
   
    stringToDict(oldLine, oldDict);
    stringToDict(newLine, newDict);
   
    if (compareDicts(newDict, oldDict, compareResult)) {
      for (int i = 0; i < NUM_COMPARE_FIELD; ++i) {
        map<char, vector<string> >::const_iterator it =
          compareResult.find(COMPARE_FIELD[i]);
        if (!it->second.empty()) {
          printf("%c%s", COMPARE_FIELD[i], it->second[0].c_str());
          for (int k = 1; k < it->second.size(); ++k) {
            printf(",%s", it->second[k].c_str());
          }
          printf("\n");
        }
      }
    } else {
      printf("No changes\n");
    }
    printf("\n");
    
    numTest--;
  }

  return 0;
}

