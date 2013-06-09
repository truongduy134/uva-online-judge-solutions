/*******************************************************************************
 * Author: Nguyen Truong Duy
 ********************************************************************************/

/* Methodology:
 *	+ This is a graph traversal problem.
 *	+ We build a weighted directed graph G as follows:
 *		- Each item is a vertex.
 *		- For each assertion c ITEM_A = d ITEM_B, we have
 *			+ A directed edge from ITEM_A to ITEM_B with weight d / c
 *			+ A directed edge from ITEM_B to ITEM_A with weight c / d
 *		  (We must have a class Fraction to represent rational numbers)
 *	+ Then for each query ? ITEM_A = ? ITEM_B, we perform a graph traversal (BFS or DFS)
 *		to find a path from ITEM_A to ITEM_B
 *	  If such a path exist, denoted as P = u1 u2 ... u(k), then compute
 *		m / n = w(u1, u2) * w(u2, u3) * ... * w(u(k - 1), u(k))
 *	  Then we answer n ITEM_A = m ITEM_B	
 */

#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <queue>

using namespace std;

class Fraction {
private:
	long long _denom, _numer;

	void simplifyFraction();
	static long long computeGCD(long long a, long long b);

public:
	Fraction() : _numer(0), _denom(1) {}
	Fraction(int numer, int denom) : _numer(numer), _denom(denom) { simplifyFraction(); }
	Fraction(const Fraction & other) : _numer(other._numer), _denom(other._denom) {}
	long long getDenom() const { return _denom; }
	long long getNumer() const { return _numer; }
	
	Fraction & operator= (const Fraction & rhs);
	const Fraction operator* (const Fraction & rhs) const;
	Fraction & operator*= (const Fraction & rhs);	 
};

long long Fraction::computeGCD(long long a, long long b)
{
	while(b)
	{
		long long remainder = a % b;
		a = b;
		b = remainder;
	}

	return a;
}

void Fraction::simplifyFraction()
{
	long long gcd = computeGCD(_numer, _denom);
	_numer /= gcd;
	_denom /= gcd;
}

Fraction & Fraction::operator= (const Fraction & rhs)
{
	if(this == &rhs)
		return *this;

	_numer = rhs._numer;
	_denom = rhs._denom;
	return *this;
}

Fraction & Fraction::operator*= (const Fraction & rhs)
{
	_numer *= rhs._numer;
	_denom *= rhs._denom;

	simplifyFraction();

	return *this;
}

const Fraction Fraction::operator* (const Fraction & rhs) const
{
	Fraction result(*this);

	result *= rhs;
	return result;
}

const char ASSERTION = '!';
const char QUERY = '?';
const char END_INPUT = '.';
const int MAX_LEN = 20;

Fraction getPathCost(const vector<vector<pair<int, Fraction> > > & adjList, 
		     int src, int dest);
int getItemId(map<string, int> & mapItemToId, const string & item, int * idToAssign);

int main(void)
{
	vector<vector<pair<int, Fraction> > > adjList;
	vector<pair<int, Fraction> > emptyList;

	map<string, int> mapItemToId;
	char str[MAX_LEN + 1], itemOne[MAX_LEN + 1], itemTwo[MAX_LEN + 1];
	int amountOne, amountTwo, idToAssign, idOne, idTwo;

	idToAssign = 0;
	while(1)
	{
		scanf("%s", str);
		if(str[0] == ASSERTION)
		{
			scanf("%d %s %s %d %s", &amountOne, itemOne,
				str, &amountTwo, itemTwo);
			idOne = getItemId(mapItemToId, itemOne, &idToAssign);
			if(idOne >= (int) adjList.size())
				adjList.push_back(emptyList);
			idTwo = getItemId(mapItemToId, itemTwo, &idToAssign);
			if(idTwo >= (int) adjList.size())
				adjList.push_back(emptyList);

			adjList[idOne].push_back(pair<int, Fraction> (idTwo,
				Fraction(amountTwo, amountOne)));
			adjList[idTwo].push_back(pair<int, Fraction> (idOne,
				Fraction(amountOne, amountTwo)));
		}

		if(str[0] == QUERY)
		{
			scanf("%s %s %s", itemOne, str, itemTwo);
			idOne = mapItemToId[itemOne];
			idTwo = mapItemToId[itemTwo];

			Fraction cost = getPathCost(adjList, idOne, idTwo);

			if(cost.getNumer() < 0)
				printf("? %s = ? %s\n", itemOne, itemTwo);
			else
				printf("%lld %s = %lld %s\n", cost.getDenom(),
					itemOne, cost.getNumer(), itemTwo);
		}
	
		if(str[0] == END_INPUT)
			break;
	}
	return 0;
}

int getItemId(map<string, int> & mapItemToId, const string & item, int * idToAssign)
{
	map<string, int>::iterator it = mapItemToId.find(item);

	int returnId = 0;
	if(it == mapItemToId.end())
	{
		returnId = *idToAssign;
		mapItemToId[item] = returnId;
		(*idToAssign)++;
	}
	else
		returnId = it->second;

	return returnId;
}

Fraction getPathCost(const vector<vector<pair<int, Fraction> > > & adjList, 
		     int src, int dest)
{
	int numV = (int) adjList.size();

	queue<pair<int, Fraction> > vQueue;
	vector<bool> visited(numV, false);

	vQueue.push(pair<int, Fraction> (src, Fraction(1, 1)));
	visited[src] = true;

	while(!vQueue.empty())
	{
		int v = vQueue.front().first;
		Fraction cost = vQueue.front().second;
		vQueue.pop();

		if(v == dest)
			return cost;
		for(int ind = 0; ind < (int) adjList[v].size(); ind++)
		{
			int nextV = adjList[v][ind].first;

			if(visited[nextV] == false)
			{
				visited[nextV] = true;
				Fraction nextCost = cost * adjList[v][ind].second;
				vQueue.push(pair<int, Fraction> (nextV, nextCost));
			}
		}
	}

	// Invalid. There is no path from src to dest
	return Fraction(-1, 1);
}
