/**********************************************************************
 * Author: Nguyen Truong Duy
 **********************************************************************/
#include <cstdio>
#include <vector>

using namespace std;

/* Methodology:
 *	+ A simple polygon has a critical point if and only if is it NOT CONVEX.
 *	+ To check convexity of a polygon, we check if all three consecutive vertices have the same turn (using cross product).
 *
 * Time complexity: O(N) where N is the number of vertices.
 */

struct Point {
	int x, y;

	Point() { x = y = 0; }
	Point(int inX, int inY) { x = inX; y = inY; }
	Point(const Point & another) { x = another.x; y = another.y; }
};

bool isConvexPolygon(const vector<Point> & polygon);
int getSignCrossProduct(const Point & A, const Point & B, const Point & C);

int main(void)
{
	vector<Point> polygon;
	int numV;

	while(1)
	{
		scanf("%d", &numV);
		if(!numV)
			break;

		polygon.assign(numV, Point());

		for(int i = 0; i < numV; i++)
		{
			scanf("%d %d", &polygon[i].x, &polygon[i].y);
		}

		if(isConvexPolygon(polygon))
			printf("No\n");
		else
			printf("Yes\n");
	}
	return 0;
}

// Assume vertices are listed in clockwise (or anti-clockwise) order
bool isConvexPolygon(const vector<Point> & polygon)
{
	int numV = (int) polygon.size();

	if(numV <= 2)
		return true;	// Convex by default

	bool nonZeroFlg = false;
	int turnDirection, temp;

	Point A, B, C;

	for(int i = 0; i < numV; i++)
	{
		A = polygon[i];
		if(i + 1 == numV)
			B = polygon[0];
		else
			B = polygon[i + 1];
		if(i + 2 >= numV)
			C = polygon[i + 2 - numV];
		else
			C = polygon[i + 2];

		temp = getSignCrossProduct(A, B, C);
		if(temp != 0)
		{
			if(nonZeroFlg == true)
			{
				if(temp != turnDirection)
					return false;
			}
			else
			{
				turnDirection = temp;
				nonZeroFlg = true;
			}
		}
	}

	return true;
}

int getSignCrossProduct(const Point & A, const Point & B, const Point & C)
{
	// Let AB = (a1, a2) and BC = (b1, b2)
	int a1 = B.x - A.x, a2 = B.y - A.y,
	    b1 = C.x - B.x, b2 = C.y - B.y;
	
	int temp = a1 * b2 - a2 * b1;

	if(temp < 0)
		return -1;
	if(temp > 0)
		return 1;
	return 0;
}
