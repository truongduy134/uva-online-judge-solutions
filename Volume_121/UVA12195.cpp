/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Note: This program contains C++ 11 syntax
 */

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define MAX_STRING_LENGTH 500
#define SCALED_STANDARD_DURATION 64
#define END_INPUT_CHAR '*'

const map<int, int> NOTE_TO_DURATION_MAP = {
  {87, 64},
  {72, 32},
  {81, 16},
  {69, 8},
  {83, 4},
  {84, 2},
  {88, 1}
};
 
void getCompositionMeasures(
    vector<string>& measures,
    char * composition) {
  const static char delimiter[] = "/\n";

  measures.clear();

  char * token = strtok(composition, delimiter);
  while (token) {
    if (token[0] != '\0') {
      measures.push_back(token);
    }
    token = strtok(NULL, delimiter);
  }  
}
 
int countNumCorrectMeasures(const vector<string>& measures) {
  int numCorrectMeasure = 0;
  for (int i = 0; i < measures.size(); ++i) {
    const string & measure = measures[i];
    int duration = 0;

    for (int k = 0; k < measure.size(); ++k) {
      map<int, int>::const_iterator it =
        NOTE_TO_DURATION_MAP.find(measure[k]);
      if (it != NOTE_TO_DURATION_MAP.end()) {
        duration += it->second;
      }      
    }

    if (duration == SCALED_STANDARD_DURATION) {
      numCorrectMeasure++;
    }
  }
  return numCorrectMeasure;
}

int main(void) {
  char composition[MAX_STRING_LENGTH + 1];
  vector<string> measures;

  while (1) {
    gets(composition);
    if (composition[0] == END_INPUT_CHAR) {
      break;
    }

    getCompositionMeasures(measures, composition);
    printf("%d\n", countNumCorrectMeasures(measures));     
  }
  
  return 0;
}
