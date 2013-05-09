#include <cstdio>
#include <vector>

using namespace std;

class Point;

class Rectangle {
private:
    int _xMax, _xMin, _yMax, _yMin;

public:
    Rectangle() : _xMax(0), _xMin(0), _yMax(0), _yMin(0) {}
    Rectangle(int xMax, int xMin, int yMax, int yMin) : _xMax(xMax), _xMin(xMin), _yMax(yMax), _yMin(yMin) {}
    Rectangle(const Rectangle & obj) : _xMax(obj._xMax), _xMin(obj._xMin), _yMax(obj._yMax), _yMin(obj._yMin) {}
    ~Rectangle() {}

    bool containsPoint(const Point & point) const;
};

class Point {
private:
    int _xCoord, _yCoord;

public:
    Point() : _xCoord(0), _yCoord(0) {}
    Point(int xCoord, int yCoord) : _xCoord(xCoord), _yCoord(yCoord) {}
    Point(const Point & point) : _xCoord(point._xCoord), _yCoord(point._yCoord) {}
    ~Point() {}

friend class Rectangle;
};

bool Rectangle::containsPoint(const Point & point) const
{
    if(_xMin < point._xCoord && point._xCoord < _xMax &&
       _yMin < point._yCoord && point._yCoord < _yMax)
        return true;

    return false;
}

void buildBipartiteGraph(vector<vector<int> > & adjList, const vector<Rectangle> & slideVect,
                         const vector<Point> & pointNumVect);
bool findAndAugmentMatching(const vector<vector<int> > & adjList, int leftV, vector<int> & assignedLeftPartner,
                            vector<bool> & visited, int avoidLeftV, int avoidRightV);
void getUnambiguousMatching(const vector<vector<int> > & adjList, int sizeLeftSet, vector<int> & uniqueMatching);
int getMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet, vector<int> & assignedLeftPartner,
                       int avoidLeftV, int avoidRightV);

int main(void)
{
    vector<Rectangle> slideVect;
    vector<Point> pointNumVect;
    vector<vector<int> > adjList;
    int numSlide, xMin, xMax, yMin, yMax, xCoord, yCoord, caseId;
    vector<int> uniqueMatching;

   // freopen("in.txt", "r", stdin);

    caseId = 1;
    while(1)
    {
        scanf("%d", &numSlide);
        if(numSlide == 0)
            break;

        slideVect.clear();
        pointNumVect.clear();

        for(int i = 0; i < numSlide; i++)
        {
            scanf("%d %d %d %d", &xMin, &xMax, &yMin, &yMax);
            Rectangle slide(xMax, xMin, yMax, yMin);
            slideVect.push_back(slide);
        }

        for(int i = 0; i < numSlide; i++)
        {
            scanf("%d %d", &xCoord, &yCoord);
            Point pointNum(xCoord, yCoord);
            pointNumVect.push_back(pointNum);
        }

        buildBipartiteGraph(adjList, slideVect, pointNumVect);

        getUnambiguousMatching(adjList, numSlide, uniqueMatching);

        printf("Heap %d\n", caseId);
        int paper;
        for(paper = 0; paper < numSlide; paper++)
            if(uniqueMatching[paper] >= 0)
                    break;
        if(paper == numSlide)
            printf("none\n");
        else
        {
            printf("(%c,%d)", paper + 'A', uniqueMatching[paper] - numSlide + 1);

            paper++;
            while(paper < numSlide)
            {
                if(uniqueMatching[paper] >= 0)
                    printf(" (%c,%d)", paper + 'A', uniqueMatching[paper] - numSlide + 1);

                paper++;
            }
            printf("\n");
        }
        printf("\n");

        caseId++;
    }

    return 0;
}

void buildBipartiteGraph(vector<vector<int> > & adjList, const vector<Rectangle> & slideVect,
                         const vector<Point> & pointNumVect)
{
    vector<int> emptyList;
    int sizeLeftSet = (int) slideVect.size();

    adjList.assign(sizeLeftSet << 1, emptyList);

    for(int slide = 0; slide < sizeLeftSet; slide++)
        for(int point = 0; point < sizeLeftSet; point++)
            if(slideVect[slide].containsPoint(pointNumVect[point]))
                adjList[slide].push_back(point + sizeLeftSet);
}

void getUnambiguousMatching(const vector<vector<int> > & adjList, int sizeLeftSet, vector<int> & uniqueMatching)
{
    int numMaximumMatching, numAdjustMatching;

    int numV = (int) adjList.size();

    vector<int> assignedLeftPartner;

    numMaximumMatching = getMaximumMatching(adjList, sizeLeftSet, assignedLeftPartner, -1, -1);

    uniqueMatching.assign(sizeLeftSet, -1);
    for(int i = sizeLeftSet; i < numV; i++)
        if(assignedLeftPartner[i] >= 0)
            uniqueMatching[assignedLeftPartner[i]] = i;

    // Remove ambiguous (not unique) matching edge
    for(int leftV = 0; leftV < sizeLeftSet; leftV++)
        if(uniqueMatching[leftV] >= 0)
        {
            numAdjustMatching = getMaximumMatching(adjList, sizeLeftSet, assignedLeftPartner, leftV, uniqueMatching[leftV]);

            if(numAdjustMatching == numMaximumMatching)
                // This is not a unique matching
                uniqueMatching[leftV] = -1;
        }
}

// We should not consider the edge (avoidLeftV, avoidRightV)
int getMaximumMatching(const vector<vector<int> > & adjList, int sizeLeftSet, vector<int> & assignedLeftPartner,
                       int avoidLeftV, int avoidRightV)
{
    int numMatching = 0, numV = (int) adjList.size();
    vector<bool> visited;

    assignedLeftPartner.assign(numV, -1);

    for(int leftV = 0; leftV < sizeLeftSet; leftV++)
    {
        visited.assign(sizeLeftSet, false);
        if(findAndAugmentMatching(adjList, leftV, assignedLeftPartner, visited, avoidLeftV, avoidRightV))
            numMatching++;
    }

    return numMatching;
}

bool findAndAugmentMatching(const vector<vector<int> > & adjList, int leftV, vector<int> & assignedLeftPartner,
                            vector<bool> & visited, int avoidLeftV, int avoidRightV)
{
    if(visited[leftV])
        return false;

    visited[leftV] = true;

    int rightV;
    for(int ind = 0; ind < (int) adjList[leftV].size(); ind++)
    {
        rightV = adjList[leftV][ind];

        if(leftV == avoidLeftV && rightV == avoidRightV)
            continue;

        if(assignedLeftPartner[rightV] == -1 || findAndAugmentMatching(adjList, assignedLeftPartner[rightV],
                                assignedLeftPartner, visited, avoidLeftV, avoidRightV))
        {
            assignedLeftPartner[rightV] = leftV;
            return true;
        }
    }

    return false;
}
