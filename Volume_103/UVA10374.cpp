/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/**
 * Straightforward problem.
 *
 * Special case: When the ballot list contains only invalid candidate
 * names (names that do not appear in the candidate - party list),
 * we should print 'tie'
 */

#include <cstdio>
#include <map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define MAX_SIZE 80

void getNameToNumVoteMap(
    map<string, int>& nameToNumVoteMap,
    const vector<string>& names) {
  nameToNumVoteMap.clear();
  for (int i = 0; i < names.size(); ++i) {
    if (nameToNumVoteMap.find(names[i]) !=
        nameToNumVoteMap.end()) {
      nameToNumVoteMap[names[i]]++;
    } else {
      nameToNumVoteMap[names[i]] = 1;
    }
  }
}

int getMaxNumVote(
    const map<string, int>& nameToNumVoteMap) {
  int maxNumVote = 0;
  for (map<string, int>::const_iterator
       it = nameToNumVoteMap.begin();
       it != nameToNumVoteMap.end(); ++it) {
    if (it->second > maxNumVote) {
      maxNumVote = it->second;
    }  
  }
  return maxNumVote;
}

pair<string, bool> getWinningParty(
    const vector<string> ballots,
    const map<string, string>& nameToPartyMap) {
  if (ballots.empty()) {
    return make_pair("", false);
  }

  map<string, int> nameToNumVoteMap;
  getNameToNumVoteMap(nameToNumVoteMap, ballots);

  int maxNumVote = getMaxNumVote(nameToNumVoteMap);
  bool foundWinning = false;
  string winningParty;

  for (map<string, int>::const_iterator
       it = nameToNumVoteMap.begin();
       it != nameToNumVoteMap.end(); ++it) {
    if (it->second == maxNumVote) {
      if (!foundWinning) {
        foundWinning = true;
        winningParty = nameToPartyMap.find(it->first)->second;
      } else { // Tie
        return make_pair("", false);
      }      
    }  
  }

  return make_pair(winningParty, true);
}

int main(void) {
  int numTest, numCandidate, numBallot;
  char name[MAX_SIZE + 1];
  char party[MAX_SIZE + 1];
  char trash[2];
  map<string, string> nameToPartyMap;
  vector<string> ballots;

  scanf("%d", &numTest);
  gets(trash);
  while (numTest) {  
    ballots.clear();
    nameToPartyMap.clear();

    gets(trash);

    scanf("%d", &numCandidate);
    gets(trash);
    for (int i = 0; i < numCandidate; ++i) {
      gets(name);
      gets(party);
      nameToPartyMap[name] = party;
    }

    scanf("%d", &numBallot);
    gets(trash);
    for (int i = 0; i < numBallot; ++i) {
      gets(name);
      if (nameToPartyMap.find(name) != nameToPartyMap.end()) {
        ballots.push_back(name);
      }
    }

    pair<string, bool> result = getWinningParty(
      ballots, nameToPartyMap);
    if (!result.second) {
      printf("tie\n");
    } else {
      printf("%s\n", result.first.c_str());
    }
    
    if (numTest > 1) {
      printf("\n");
    }
  
    numTest--;
  }  
  return 0;
}

