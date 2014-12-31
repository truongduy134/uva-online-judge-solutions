/*******************************************************
 * Author: Nguyen Truong Duy
 *******************************************************/

/* Methodology:
 * - Straightforward computational geometry problem.
 * - Let C(i) is the point on the i-th segment A(i)B(i) that is closet to M.
 *   To find C(i), we find the projection P of M on the line through A(i), B(i).
 *   If P lies inside segment A(i)B(i), then C(i) = P. Otherwise, C(i) = A(i)
 *   or B(i) depending on which point is nearer to M.
 * - The final result is a point X among C(0), C(1), ..., C(N - 1) that has
 *   the smallest distance to M.
 *
 * - Time complexity: O(N) where N is the number of segments.
 */

#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

#define EPSILON 0.00000000001L
#define INF 10000000000.0

struct Point2f {
  double x, y;
};

struct Line2f {
  double a, b, c;
};

void constructLine2f(Line2f& line, const Point2f& A, const Point2f& B) {
  double vX = A.x - B.x;
  double vY = A.y - B.y;
  line.a = -vY;
  line.b = vX;
  line.c = vY * A.x - vX * A.y;
}

bool findIntersection(
    const Line2f& line1,
    const Line2f& line2,
    Point2f& intersection) {
  double delta = line1.a * line2.b - line1.b * line2.a;
  if (abs(delta) < EPSILON) {
    return false;
  }
  intersection.x = (-line1.c * line2.b + line2.c * line1.b) / delta;
  intersection.y = (-line1.a * line2.c + line2.a * line1.c) / delta;
  return true;
}

double squareDist(const Point2f& A, const Point2f&B) {
  double deltaX = A.x - B.x;
  double deltaY = A.y - B.y;
  return deltaX * deltaX + deltaY * deltaY;
}

// Finds a point on the segment AB that is closet to M.
void closetPointOnSegment(
    const Point2f& M,
    const Point2f& A,
    const Point2f& B,
    Point2f& closetPoint) {
  Line2f lineAB;
  constructLine2f(lineAB, A, B);
  Line2f lineV;
  lineV.a = -lineAB.b;
  lineV.b = lineAB.a;
  lineV.c = -lineV.a * M.x - lineV.b * M.y;

  Point2f intersection;
  findIntersection(lineV, lineAB, intersection);
  if (max(squareDist(intersection, A), squareDist(intersection, B)) >
      squareDist(A, B)) {
    if (squareDist(M, A) < squareDist(M, B)) {
      closetPoint = A;
    } else {
      closetPoint = B;
    }
  } else {
    closetPoint = intersection;
  }
}

int main(void) {
  vector<Point2f> railway;
  int numSegments;
  Point2f M, p, closetP;
  double minSquareDist, d;

  while (scanf("%lf %lf", &M.x, &M.y) > 0) {
    railway.clear();
    scanf("%d", &numSegments);
    for (int i = 0; i <= numSegments; ++i) {
      scanf("%lf %lf", &p.x, &p.y);
      railway.push_back(p);
    }

    minSquareDist = INF;
    for (int i = 0; i < numSegments; ++i) {
      closetPointOnSegment(M, railway[i], railway[i + 1], p);
      d = squareDist(M, p);
      if (d < minSquareDist) {
        minSquareDist = d;
        closetP = p;
      }
    }

    printf("%.4lf\n%.4lf\n", closetP.x, closetP.y);
  }

  return 0;
}
