#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

bool isFeasibleExchangeProgram(const vector<pair<int, int> > & exchangeChoice);

int main(void)
{
	int numStudent, from, to;
	vector<pair<int, int> > exchangeChoice;

	while(1)
	{
		scanf("%d", &numStudent);
		if(numStudent == 0)
			break;

		exchangeChoice.assign(numStudent, pair<int, int> () );
		for(int i = 0; i < numStudent; i++)
		{
			scanf("%d %d", &from, &to);
			exchangeChoice[i] = pair<int, int> (from, to);
		}

		if(isFeasibleExchangeProgram(exchangeChoice))
			printf("YES\n");
		else
			printf("NO\n");

	}
	return 0;
}

bool isFeasibleExchangeProgram(const vector<pair<int, int> > & exchangeChoice)
{
	int numStudent = (int) exchangeChoice.size();

	if(numStudent & 1)
		// there is an odd number of students
		return false;

	// Divide into 2 lists
	vector<pair<int, int> > fromLessTo, toLessFrom;

	for(int i = 0; i < numStudent; i++)
		if(exchangeChoice[i].first < exchangeChoice[i].second)
			fromLessTo.push_back(exchangeChoice[i]);
		else
			toLessFrom.push_back(exchangeChoice[i]);

	if(fromLessTo.size() != toLessFrom.size())
		return false;

	// Reverse each pair in one of the lists.
	for(int i = 0; i < toLessFrom.size(); i++)
	{
		int temp = toLessFrom[i].first;
		toLessFrom[i].first = toLessFrom[i].second;
		toLessFrom[i].second = temp;
	}

	// Sort the two lists
	sort(toLessFrom.begin(), toLessFrom.end());
	sort(fromLessTo.begin(), fromLessTo.end());

	// The exchange program is feasible if the two lists are the same.
	for(int i = 0; i < toLessFrom.size(); i++)
		if(toLessFrom[i] != fromLessTo[i])
			return false;

	return true;
}
