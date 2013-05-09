#include <cstdio>
#include <cmath>
#include <utility>

using namespace std;

#define EPSILON 0.0000000001

typedef struct {
	int xCoord, yCoord;
} Point;

typedef struct {
    	long double xCoord, yCoord;
} RealPoint;

class Line {
private:
    	// Line is represented as a x + b y + c = 0
    	long double _a, _b, _c;
public:
    	static const int INTERSECT = 1;
    	static const int SAME = 2;
    	static const int PARALLEL = 3;

    	Line() : _a(0), _b(0), _c(0) {}
    	Line(const Point * pA, const Point * pB);
    	Line(const Line & another): _a(another._a), _b(another._b), _c(another._c) {}
    	~Line() {}

    	void resetParam(const Point *pA, const Point *pB);
    	pair<int, RealPoint> findIntersect(const Line & another);
    	bool areParallel(const Line & another);
    	bool areSame(const Line & another);
};

Line::Line(const Point * pA, const Point * pB)
{
    	resetParam(pA, pB);
}

void Line::resetParam(const Point * pA, const Point * pB)
{
   	_a = pB->yCoord - pA->yCoord;
    	_b = pA->xCoord - pB->xCoord;
    	_c = -(_a * pA->xCoord + _b * pA->yCoord);
}

bool Line::areParallel(const Line & another)
{
    	return fabs(_a * another._b - _b * another._a) < EPSILON;
}

bool Line::areSame(const Line & another)
{
    	return areParallel(another) && fabs(_a * another._c - _c * another._a) < EPSILON 
				    && fabs(_b * another._c - _c * another._b) < EPSILON;
}

pair<int, RealPoint> Line::findIntersect(const Line & another)
{
    	RealPoint intersectP;
    	intersectP.xCoord = 0;
    	intersectP.yCoord = 0;

    	if(areSame(another))
        	return make_pair(SAME, intersectP);

    	if(areParallel(another))
        	return make_pair(PARALLEL, intersectP);

    	long double det = _b * another._a - _a * another._b;

    	intersectP.yCoord = -(_c * another._a - _a * another._c) / det;
    	if(fabs(intersectP.yCoord) < EPSILON)
		intersectP.yCoord = 0.0; 
    	intersectP.xCoord = (_c * another._b - _b * another._c) / det;
	if(fabs(intersectP.xCoord) < EPSILON)
		intersectP.xCoord = 0.0;
    	return make_pair(INTERSECT, intersectP);
}

int main(void)
{
    	Point pStart, pEnd;
    	Line lineArr[2];
    	int T;
    	pair<int, RealPoint> result;

    	scanf("%d", &T);

    	printf("INTERSECTING LINES OUTPUT\n");
    	while(T)
    	{
        	for(int i = 0; i < 2; i++)
        	{
            		scanf("%d %d %d %d", &pStart.xCoord, &pStart.yCoord,
                                 	     &pEnd.xCoord, &pEnd.yCoord);
            		lineArr[i].resetParam(&pStart, &pEnd);
        	}

        	result = lineArr[0].findIntersect(lineArr[1]);
        	if(result.first == Line::PARALLEL)
            		printf("NONE\n");
        	else
        	{
            		if(result.first == Line::SAME)
                		printf("LINE\n");
            		else
                		printf("POINT %.2Lf %.2Lf\n", result.second.xCoord,
                                              		      result.second.yCoord);
        	}
        	T--;
    	}
    	printf("END OF OUTPUT\n");

    	return 0;
}
