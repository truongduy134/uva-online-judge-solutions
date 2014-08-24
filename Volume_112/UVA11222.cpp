/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define NUM_PEOPLE 3

int main(void) {
  int numTest, numProblem, problem, caseNumber;

  scanf("%d", &numTest);
  
  map<int, vector<int> > mapProblemToSolvers;
  vector<set<int> > specialProblems;

  caseNumber = 1;
  while (caseNumber <= numTest) {
    mapProblemToSolvers.clear();
    specialProblems.assign(NUM_PEOPLE, set<int>());

    // Reading inputs
    for (int p = 0; p < NUM_PEOPLE; p++) {
      scanf("%d", &numProblem);
      for (int i = 0; i < numProblem; ++i) {
        scanf("%d", &problem);
        if (mapProblemToSolvers.find(problem) ==
            mapProblemToSolvers.end()) {
          mapProblemToSolvers[problem] = vector<int>();
        }
        mapProblemToSolvers[problem].push_back(p);
      }
    }

    for (map<int, vector<int> >::const_iterator it = mapProblemToSolvers.begin();
         it != mapProblemToSolvers.end(); ++it) {
      if (it->second.size() == 1) {
        specialProblems[it->second[0]].insert(it->first);
      }
    }

    int maxNumSpecial = 0;
    for (int i = 0; i < NUM_PEOPLE; ++i) {
      if (specialProblems[i].size() > maxNumSpecial) {
        maxNumSpecial = specialProblems[i].size();
      }
    }

    printf("Case #%d:\n", caseNumber);
    for (int i = 0; i < NUM_PEOPLE; ++i) {
      if (specialProblems[i].size() == maxNumSpecial) {
        printf("%d %d", i + 1, (int)specialProblems[i].size());
        for (set<int>::const_iterator it = specialProblems[i].begin();
             it != specialProblems[i].end(); ++it) {
          printf(" %d", *it);
        }
        printf("\n");
      }
    }

    caseNumber++;
  }

  return 0;
}

