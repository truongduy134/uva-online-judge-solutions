/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <vector>

using namespace std;

int main(void) {
  int numProbs, numTeams, numSubs;
  int time, teamId, problemId;
  char problem[2], verdict[4];

  vector<int> lastBloodTeams, lastBloodTime;
  vector<unordered_set<int> > passedTeams;

  scanf("%d %d %d", &numProbs, &numTeams, &numSubs);

  lastBloodTeams.assign(numTeams, -1);
  lastBloodTime.assign(numTeams, -1);
  passedTeams.assign(numTeams, unordered_set<int>());

  for (int i = 0; i < numSubs; ++i) {
    scanf("%d %d %s %s", &time, &teamId, problem, verdict);

    if (strcmp(verdict, "No") == 0) {
      continue;
    }

    problemId = problem[0] - 'A';
    if (passedTeams[problemId].find(teamId) == passedTeams[problemId].end()) {
      passedTeams[problemId].insert(teamId);
      lastBloodTeams[problemId] = teamId;
      lastBloodTime[problemId] = time;
    }
  }

  for (int i = 0; i < numProbs; ++i) {
    printf("%c", i + 'A');
    if (lastBloodTeams[i] < 0) {
      printf(" - -\n");
    } else {
      printf(" %d %d\n", lastBloodTime[i], lastBloodTeams[i]);
    }
  }

  return 0;
}
