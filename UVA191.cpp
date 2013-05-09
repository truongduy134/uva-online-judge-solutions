#include <iostream>

using namespace std;

class Point3D
{
    public:
        long long m_xCoord, m_yCoord, m_zCoord;

    public:
        /* Constructor */
        Point3D();
        Point3D(long long xCoord, long long yCoord, long long zCoord);
        Point3D(const Point3D &another);
        /* Destructor */
        ~Point3D();
        /* Other function */
        long long squareDistance(const Point3D &another) const;
};

class Vector3D
{
    public:
        long long m_xCoordV, m_yCoordV, m_zCoordV;

    public:
        /* Constructor */
        Vector3D();
        Vector3D(long long xCoord, long long yCoord, long long zCoord);
        Vector3D(const Point3D &inputPoint3D);
        Vector3D(const Point3D &A, const Point3D &B);
        Vector3D(const Vector3D &copy);

        /* Destructor */
        ~Vector3D();

        long long squareLength();
        long long innerProduct(const Vector3D &another);
        Vector3D crossProduct(const Vector3D &another);
        bool isZero();
};

class LineSegm
{
    public:
        Point3D m_startP, m_endP;

    public:
        /* Constructor */
        LineSegm();
        LineSegm(const Point3D &start, const Point3D &end);
        LineSegm(const LineSegm &another);
        // Desstructor
        ~LineSegm();

        bool onLine(const Point3D &inputPoint3D) const;
        bool onSegment(const Point3D &inputPoint3D) const;
        bool oppositeSide(const Point3D &A, const Point3D &B) const;
        bool doIntersect(const LineSegm &another) const;
};

class Rectangle
{
    // Note: If A is the top left point and C is the bottom right point of the rectangle ABCD
    //  Then the top right point B has coordinates (C.x, A.y) and
    //       the bottom left point D has coordinates (A.x, C.y)
    public:
        Point3D m_topLeft, m_bottomRight;

    public:
        /* Constructors */
        Rectangle(const Point3D &topLeft, const Point3D &bottomRight);
        ~Rectangle();

        bool isInRectangle(const Point3D &inputPoint);
        bool doIntersect(const LineSegm &segment);

};
Point3D::Point3D()
{
    // Create the origin
    m_xCoord = m_yCoord = m_zCoord = 0;
}

Point3D::Point3D(long long xCoord, long long yCoord, long long zCoord)
{
    m_xCoord = xCoord;
    m_yCoord = yCoord;
    m_zCoord = zCoord;
}

Point3D::Point3D(const Point3D &another)
{
    m_xCoord = another.m_xCoord;
    m_yCoord = another.m_yCoord;
    m_zCoord = another.m_zCoord;
}

Point3D::~Point3D()
{
    return;
}

// Return the square of the distance from this Point3D to the input Point3D.
long long Point3D::squareDistance(const Point3D &another) const
{
    return (m_xCoord - another.m_xCoord) * (m_xCoord - another.m_xCoord) + (m_yCoord - another.m_yCoord) * (m_yCoord - another.m_yCoord) +
           (m_zCoord - another.m_zCoord) * (m_zCoord - another.m_zCoord);
}

 /* Default constructor: Create the zero vector */
Vector3D::Vector3D()
{
    m_xCoordV = m_yCoordV = m_zCoordV = 0;
}

Vector3D::Vector3D(long long xCoord, long long yCoord, long long zCoord)
{
    m_xCoordV = xCoord;
    m_yCoordV = yCoord;
    m_zCoordV = zCoord;
}

Vector3D::Vector3D(const Point3D &inputPoint3D)
{
    m_xCoordV = inputPoint3D.m_xCoord;
    m_yCoordV = inputPoint3D.m_yCoord;
    m_zCoordV = inputPoint3D.m_zCoord;
}

Vector3D::Vector3D(const Point3D &A, const Point3D &B)
{
    // Create the vector AB
    m_xCoordV = B.m_xCoord - A.m_xCoord;
    m_yCoordV = B.m_yCoord - A.m_yCoord;
    m_zCoordV = B.m_zCoord - A.m_zCoord;
}

Vector3D::Vector3D(const Vector3D &copy)
{
    m_xCoordV = copy.m_xCoordV;
    m_yCoordV = copy.m_yCoordV;
    m_zCoordV = copy.m_zCoordV;
}

/* Destructor */
Vector3D::~Vector3D()
{
    return;
}

// Return the square of the vector length
long long Vector3D::squareLength()
{
    return m_xCoordV * m_xCoordV + m_yCoordV * m_yCoordV + m_zCoordV * m_zCoordV;
}

long long Vector3D::innerProduct(const Vector3D &another)
{
    return m_xCoordV * another.m_xCoordV + m_yCoordV * another.m_yCoordV + m_zCoordV * another.m_zCoordV;
}

Vector3D Vector3D::crossProduct(const Vector3D &another)
{
    long long xCoord, yCoord, zCoord;

    xCoord = m_yCoordV * another.m_zCoordV - m_zCoordV * another.m_yCoordV;
    yCoord = -(m_xCoordV * another.m_zCoordV - m_zCoordV * another.m_xCoordV);
    zCoord = m_xCoordV * another.m_yCoordV - m_yCoordV * another.m_xCoordV;

    return Vector3D(xCoord, yCoord, zCoord);
}

bool Vector3D::isZero()
{
    return (m_xCoordV == 0) && (m_yCoordV == 0) && (m_zCoordV == 0);
}

LineSegm::LineSegm()
{
    Point3D origin;
    m_startP = origin;
    m_endP = origin;
}

LineSegm::LineSegm(const Point3D &startP, const Point3D &endP)
{
    m_startP = startP;
    m_endP = endP;
}

LineSegm::LineSegm(const LineSegm &another)
{
    m_startP = another.m_startP;
    m_endP = another.m_endP;
}

LineSegm::~LineSegm()
{
    return;
}

/* Return true if the input Point3D is on the extented line of the line segment
 * Return false otherwise
 *
 * Methodology:
 *  + Denote A, B to be the two endPoint3Ds of the line segment.
 *  + Denote C to be the input Point3D.
 *  + A, B, C are colinear if the cross product of vectors AB and AC is zero
 */
bool LineSegm::onLine(const Point3D &inputPoint3D) const
{
    Vector3D vectorOne(m_startP, m_endP);
    Vector3D vectorTwo(m_startP, inputPoint3D);

    Vector3D cross = vectorOne.crossProduct(vectorTwo);

    return cross.isZero();
}

bool LineSegm::onSegment(const Point3D &inputPoint3D) const
{
    if(this->onLine(inputPoint3D) == false)
        return false;

    long long lengthLine = m_startP.squareDistance(m_endP);
    if(m_startP.squareDistance(inputPoint3D) <= lengthLine && m_endP.squareDistance(inputPoint3D) <= lengthLine)
        return true;

    return false;
}

// NOTE: If one of the input Point3Ds is on the line, then
//     we consider they are on the same side of the line!
bool LineSegm::oppositeSide(const Point3D &A, const Point3D &B) const
{
    Vector3D vectorOne(m_startP, m_endP);
    Vector3D vectorTwo(m_startP, A);
    Vector3D vectorThree(m_startP, B);

    Vector3D crossOne = vectorOne.crossProduct(vectorTwo);
    Vector3D crossTwo = vectorOne.crossProduct(vectorThree);

    if(crossOne.innerProduct(crossTwo) < 0)
        return true;

    return false;
}

bool LineSegm::doIntersect(const LineSegm &another) const
{
    if(onSegment(another.m_startP) || onSegment(another.m_endP) ||
       another.onSegment(m_startP) || another.onSegment(m_endP))
       return true;

    if(this->oppositeSide(another.m_startP, another.m_endP) && another.oppositeSide(m_startP, m_endP))
        return true;

    return false;
}

Rectangle::Rectangle(const Point3D &topLeft, const Point3D &bottomRight)
{
    m_topLeft = topLeft;
    m_bottomRight = bottomRight;
}

Rectangle::~Rectangle()
{
    return;
}

bool Rectangle::isInRectangle(const Point3D &inputPoint)
{
    if(inputPoint.m_xCoord >= m_topLeft.m_xCoord && inputPoint.m_xCoord <= m_bottomRight.m_xCoord &&
       inputPoint.m_yCoord >= m_bottomRight.m_yCoord && inputPoint.m_yCoord <= m_topLeft.m_yCoord)
       return true;

    return false;
}

bool Rectangle::doIntersect(const LineSegm &segment)
{
    if(isInRectangle(segment.m_startP) || isInRectangle(segment.m_endP))
        return true;

    // Otherwise, for the line to intersect a rectangle, it must intersect with one of the four lines of the rectangle.
    Point3D A(m_topLeft);
    Point3D B(m_bottomRight.m_xCoord, m_topLeft.m_yCoord, 0);
    Point3D C(m_bottomRight);
    Point3D D(m_topLeft.m_xCoord, m_bottomRight.m_yCoord, 0);
    LineSegm AB(A, B);
    LineSegm BC(B, C);
    LineSegm CD(C, D);
    LineSegm AD(A, D);

    if(AB.doIntersect(segment) || BC.doIntersect(segment) || CD.doIntersect(segment) || AD.doIntersect(segment))
        return true;

    return false;
}

int main()
{
    int numTest;
    cin >> numTest;
    while(numTest)
    {
        Point3D lineStart, lineEnd, topLeft, bottomRight;
        long long xOne, yOne, xTwo, yTwo;

        cin >> lineStart.m_xCoord >> lineStart.m_yCoord;
        lineStart.m_zCoord = 0;
        cin >> lineEnd.m_xCoord >> lineEnd.m_yCoord;
        lineEnd.m_zCoord = 0;
        cin >> xOne>> yOne;
        cin >> xTwo >> yTwo;

        if(xOne > xTwo)
        {
            topLeft.m_xCoord = xTwo;
            bottomRight.m_xCoord = xOne;
        }
        else
        {
            topLeft.m_xCoord = xOne;
            bottomRight.m_xCoord = xTwo;
        }

        if(yOne > yTwo)
        {
            topLeft.m_yCoord = yOne;
            bottomRight.m_yCoord = yTwo;
        }
        else
        {
            topLeft.m_yCoord = yTwo;
            bottomRight.m_yCoord = yOne;
        }
        topLeft.m_zCoord = 0;
        bottomRight.m_zCoord = 0;

        LineSegm segment(lineStart, lineEnd);
        Rectangle inputRec(topLeft, bottomRight);
        if(inputRec.doIntersect(segment))
            cout << "T" << endl;
        else
            cout << "F" << endl;

        numTest--;
    }
    return 0;
}
