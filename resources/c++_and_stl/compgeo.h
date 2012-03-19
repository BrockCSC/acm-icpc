/* A library for use with computational-geometry algorithms/problems.
 * Can be used for competitve programming, but more useful as a personal library. 
 * Majority of the code used is modified code from Steven/Felix Halim and AC_RUSH.
 * 
 * Dennis Ideler, March 2012
 */

// TODO: use const where appropriate
// NOTE: Do not bother using 'const' when copying for programming contests.

#include <cmath>

//#define INF 1e9
//#define EPS 1e-9
//#define PI acos(-1.0) // alternative #define PI (2.0 * acos(0.0))

const double INF = 1e9;
const double PI = acos(-1.0);  // (2.0 * acos(0.0)) should also work.
const double EPS = 1e-9;  // Used for equality checks (substitute for 0).

double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

/*** 0D objects: Points ***/

// struct point_i { int x, y; }; // Minimalist version.

struct point_i  // Use when points given in integers.
{
  int x, y;

  point_i(void) : x(0), y(0) {}

  point_i(int _x, int _y)  // Optional constructor.
  {
    x = _x;
    y = _y;
  }
};

struct point  // Use always or when precision is needed.
{
  double x, y;
  
  point(void) : x(0.0), y(0.0) {}

  point(double _x, double _y)
  {
    x = _x;
    y = _y;
  }

  // Override 'less than' operator for sorting.
  // Ex: if we have vector<point> P, then sort(P.begin(), P.end())
  bool operator < (const point &other) const
  {
    if (fabs(x - other.x) > EPS)
      return x < other.x;  // First criteria (if x values differ).
    return y < other.y;  // Second criteria.
  }  // Alternatively, can have a comparison function for point objects.
};

bool areSame(const point_i &p1, const point_i &p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

bool areSame(const point &p1, const point &p2)
{
  return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
}

// Euclidean distance.
double dist(const point &p1, const point &p2)
{
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

template<class T> inline T sqr(const T &x)
{
  return x * x;
}

// Euclidean distance metric.
double dist(double x1, double y1, double x2, double y2)
{
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

// Euclidean Squared distance metric.
double distR(double x1, double y1, double x2, double y2)
{
  return sqr(x1-x2) + sqr(y1-y2);
}

// Rotate point p by theta degrees CCW w.r.t. to origin (0,0).
point rotate(point p, double theta)
{
  // rotation matrix R(theta) = [cos(theta) -sin(theta)]
  //                            [sin(theta)  cos(theta)]
  // usage: [x'] = R(theta) * [x]
  //        [y'] = ...      * [y]
  double rad = DEG_to_RAD(theta);
  return point(p.x * cos(rad) - p.y * sin(rad),
               p.x * sin(rad) + p.y * cos(rad));
}

/*** 1D objects: Lines ***/

// A line represented as coefficients of ax + by + c = 0.
struct line
{
  double a, b, c;

  line(point p1, point p2)  // Compute the line equation given 2 points.
  {
    if (p1.x == p2.x)  // Vertical line: default values.
    {
      a = 1.0;
      b = 0.0;
      c = -p1.x;
    }
    else
    {
      a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
      b = 1.0;
      c = -(double)(a * p1.x) - (b * p1.y);
    }
  }
  
  line(double x1, double y1, double x2, double y2)  // Given point coordinates.
  {
    if (x1 == x2)  // Vertical line: default values.
    {
      a = 1.0;
      b = 0.0;
      c = -x1;
    }
    else
    {
      a = -(double)(y1 - y2) / (x1 - x2);
      b = 1.0;
      c = -(double)(a * x1) - (b * y1);
    }
  }

  line(point p, double m)  // Given one point and gradient/slope of line.
  {
    a = -m;
    b = 1.0;
    c = -((a * p.x) + (b * p.y));
  }
};

bool areParallel(line l1, line l2)  // Check if coefficients a == b.
{
  return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(line l1, line l2)  // Check if parallel & coefficients c are equal.
{
  return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

// Checks if two lines intersect. Returns true + intersection point if intersect.
bool areIntersect(line l1, line l2, point &p)
{
  if (areSame(l1, l2)) return false;  // All points intersect!
  if (areParallel(l1, l2)) return false;  // Parallel lines do not intersect!

  // Otherwise 2 lines intersect at some point (Note: lines, not line segments).
  // Solve system of 2 linear algebraic equations with 2 unknowns.
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  if (fabs(l1.b) > EPS)  // Special case: test for vertical line.
    p.y = -(l1.a * p.x + l1.c) / l1.b;
  else
    p.y = -(l2.a * p.x + l2.c) / l2.b;
  return true;
}

struct vec  // Vector is a line segment with a direction.
{
  double x, y;  // Represented by x and y magnitude of vector.

  vec(double _x, double _y)  // Given the magnitude.
  {
    x = _x;
    y = _y;
  }

  vec(point p1, point p2)  // Given two end points.
  {
    x = p2.x - p1.x;  // TODO: should it be fabs value?
    y = p2.y - p1.y;
  }
};

vec scaleVector(vec v, double s)  // Scales the magnitude of the vector.
{
  return vec(v.x * s, v.y * s);
}

point translate(point p, vec v)  // Translate p according to v.
{
  return point(p.x + v.x, p.y + v.y);
}

void closestPoint(line l, point p, point &ans)  // Same as distToLine().
{                                     
  if (fabs(l.b) < EPS)  // Special case 1: vertical line.
  {
    ans.x = -(l.c);
    ans.y = p.y;
    return;
  }
  if (fabs(l.a) < EPS)  // Special case 2: horizontal line.
  {
    ans.x = p.x;
    ans.y = -(l.c);
    return;
  }
  
  line perpendicular(p, 1 / l.a);  // Perpendicular to l and pass through p.
  areIntersect(l, perpendicular, ans);  // Intersection point is closest point.
 }

double distToLine()
{
  // TODO
}

double distToLineSegment()
{
  // TODO
}

double cross(point p0, point p1, point p2)  // Cross product.
{
  return (p2.x - p1.x) * (p0.y - p1.y) - (p2.y - p1.y) * (p0.x - p1.x);
}

bool collinear(point p0, point p1, point p2)  // True if p2 is on line p0p1.
{
  return fabs(cross(p0, p1, p2)) < EPS;
}

bool ccw(point p0, point p1, point p2)  // True if p2 is left from p0p1.
{
  return cross(p0, p1, p2) > 0;  // Doesn't check for == 0 (i.e. collinear).
}

bool nonLeftTurn(point p0, point p1, point p2)  // True if right turn or collinear.
{
  return !ccw(p0, p1, p2) || collinear(p0, p1, p2);
}

// AC_RUSH begin
template<class T> T cross(T x0, T y0, T x1, T y1, T x2, T y2)
{
  return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}

// If cross product is positive: counterclockwise from p0p1 to p1p2.
// If cross product is negative: clockwise from p0p1 to p1p2.
// If cross product is zero: p0, p1, p2 are collinear.
int crossOper(double x0, double y0, double x1, double y1, double x2, double y2)
{
  //double t = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
  double t = cross(x0, y0, x1, y1, x2, y2);
  if (fabs(t) <= EPS)
    return 0;
  return (t < 0) ? -1 : 1;
}

// Checks if two line segments (given by their points) intersect.
bool isIntersect(double x1, double y1, double x2, double y2, double x3,
                 double y3, double x4, double y4)
{
  return crossOper(x1, y1, x2, y2, x3, y3) *
         crossOper(x1, y1, x2, y2, x4, y4) < 0 &&
         crossOper(x3, y3, x4, y4, x1, y1) *
         crossOper(x3, y3, x4, y4, x2, y2) < 0;
}

bool isMiddle(double s, double m, double t)
{
  return fabs(s - m) <= EPS || fabs(t - m) <= EPS || (s < m) != (t < m);
}
// AC_RUSH end


// TODO: finish 1D objects section before ACM practice starts.

/*** 2D objects: Circles ***/
// TODO

/*** 2D objects: Triangles ***/
// TODO

/*** 2D objects: Quadrilaterals ***/
// TODO

/*** 3D objects: Sphere ***/
// TODO
