#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

class Point {
private:
	int _xCoord, _yCoord;
public:
	Point() : _xCoord(0), _yCoord(0) { }
	Point(int xCoord, int yCoord) : _xCoord(xCoord), _yCoord(yCoord) { }
	Point(const Point & another) : _xCoord(another._xCoord), _yCoord(another._yCoord) { }
	double getDistance(Point & another) {
		return sqrt((_xCoord - another._xCoord)  * (_xCoord - another._xCoord) + (_yCoord - another._yCoord) * (_yCoord - another._yCoord));
	}

	int getXCoord() { return _xCoord; }
	int getYCoord() { return _yCoord; }		
};

void buildBipartiteGraph(vector<vector<int> > & adjList, vector<Point> & pointArr, int sizeSetOne);
int getMaximumMatching(vector<vector<int> > & adjList, int sizeSetOne, vector<int> & matching);
bool findAugmentPath(vector<vector<int> > & adjList, int vLeft, vector<int> & reverseMatching, vector<bool> &visited, vector<int> & matching);
void printMatching(vector<Point> & pointArr, int sizeSetOne, vector<int> & matching);

int main(void)
{
	int T, N, M, x, y, maxNumMatching;
	vector<Point> pointArr;
	vector<vector<int> > adjList;
	vector<int> matching;
	Point origin;
	
	scanf("%d", &T);

	while(T)
	{
		scanf("%d %d", &N, &M);
		pointArr.clear();

		for(int i = 0; i < N + M; i++)
		{
			scanf("%d %d", &x, &y);
			Point newP(x, y);
			pointArr.push_back(newP);	
		}

		buildBipartiteGraph(adjList, pointArr, N);
		
		maxNumMatching = getMaximumMatching(adjList, N, matching);

		printf("%d\n", maxNumMatching + N);
		printMatching(pointArr, N, matching);
		
		if(T != 1)
			printf("\n");	
		T--;
	}	
	return 0;
}

void buildBipartiteGraph(vector<vector<int> > & adjList, vector<Point> & pointArr, int sizeSetOne)
{
	vector<int> emptyList;
	int numV = (int) pointArr.size();
	double distance;

	adjList.assign(numV, emptyList);

	for(int i = 0; i < sizeSetOne - 1; i++)
	{
		distance = pointArr[i].getDistance(pointArr[i + 1]);

		for(int j = sizeSetOne; j < numV; j++)
		{
			if(!(pointArr[i].getDistance(pointArr[j]) + pointArr[j].getDistance(pointArr[i + 1]) > 2 * distance))
			{
				adjList[i].push_back(j);
			}
		}
	}
}

int getMaximumMatching(vector<vector<int> > & adjList, int sizeSetOne, vector<int> & matching)
{
	int numV = (int) adjList.size(), maxNumMatching = 0;

	vector<int> reverseMatching(numV, -1);
	vector<bool> visited;

	matching.assign(sizeSetOne, -1);

	for(int i = 0; i < sizeSetOne; i++)
	{
		visited.assign(sizeSetOne, false);
		if(findAugmentPath(adjList, i, reverseMatching, visited, matching))
			maxNumMatching++;
	}

	return maxNumMatching;
}

bool findAugmentPath(vector<vector<int> > & adjList, int vLeft, vector<int> & reverseMatching, vector<bool> &visited, vector<int> & matching)
{
	if(visited[vLeft])
		return false;

	visited[vLeft] = true;

	int vRight;
	for(int j = 0; j < (int) adjList[vLeft].size(); j++)
	{
		vRight = adjList[vLeft][j];

		if(reverseMatching[vRight] == -1 || findAugmentPath(adjList, reverseMatching[vRight], reverseMatching, visited, matching))
		{
			// Found a new matching
			reverseMatching[vRight] = vLeft;
			matching[vLeft] = vRight;
			return true;
		}
	}

	return false;
}

void printMatching(vector<Point> & pointArr, int sizeSetOne, vector<int> & matching)
{
	for(int i = 0; i < sizeSetOne; i++)
	{
		if(i != 0)
			printf(" ");
		printf("%d %d", pointArr[i].getXCoord(), pointArr[i].getYCoord());
		if(matching[i] >= 0)
			printf(" %d %d", pointArr[matching[i]].getXCoord(), pointArr[matching[i]].getYCoord());		
	}
	printf("\n");
} 
