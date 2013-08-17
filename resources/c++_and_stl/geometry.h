/* A library for use with computational-geometry algorithms/problems.
 * Can be used for competitve programming, but more useful as a personal library. 
 * Majority of the code used is modified code from Steven/Felix Halim and AC_RUSH.
 * 
 * Dennis Ideler, March 2012
 */

// TODO: use const where appropriate
// NOTE: Do not bother using 'const' when copying for programming contests.
// NOTE: When working with floating point, checking for equality as
//       fabs(a - b) < EPS is faster than a == b.

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

struct point_i  // Use whenever possible or points given in integers.
{
  int x, y;
  point_i(int _x = 0, int _y = 0) : x(_x), y(_y) {} // optional constructor
};

struct point  // Use only when extra precision is needed.
{
  double x, y;
  point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

  // Override 'less than' operator for sorting.
  // Ex: if we have vector<point> P, then sort(P.begin(), P.end())
  bool operator < (const point &other) const
  {
    if (fabs(x - other.x) > EPS)
      return x < other.x; 
    return y < other.y;
  }  // Alternatively, can have a comparison function for point objects.
};

// True if two points are the same.
bool areSame(const point_i &p1, const point_i &p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

// True if two points are the same.
bool areSame(const point &p1, const point &p2)
{
  return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
}

// Euclidean distance between two points.
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
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2)); // same as hypot(x1 - x2, y1 - y2);
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
// Interactive demo of line equation: http://www.analyzemath.com/line/line.htm
// We avoid the line equation y = mx + c.
struct line
{
  double a, b, c;

  line(point p1, point p2)  // Compute the line equation given 2 points.
  {
    if (fabs(p1.x - p2.x) < EPS)  // Vertical line: default values.
    {
      a = 1.0;
      b = 0.0;
      c = -p1.x;
    }
    else
    {
      a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
      b = 1.0;
      c = -(double)(a * p1.x) - p1.y;
    }
  }
  
  line(double x1, double y1, double x2, double y2)  // Given point coordinates.
  {
    if (fabs(x1 - x2) < EPS)  // Vertical line: default values.
    {
      a = 1.0;
      b = 0.0;
      c = -x1;
    }
    else
    {
      a = -(double)(y1 - y2) / (x1 - x2);
      b = 1.0;
      c = -(double)(a * x1) - y1;
    }
  }

  line(point p, double m)  // Given one point and gradient/slope of line.
  {
    a = -m;
    b = 1.0;
    c = -((a * p.x) + (b * p.y));
  }
};

// A line is horizontal if a == 0 and b != 0.
bool isHorizontal(line l)
{
  return fabs(l.a) < EPS && fabs(l.b) > EPS;
}

// A line is vertical if a != 0 and b == 0.
bool isVertical(line l)
{
  return fabs(l.a) > EPS && fabs(l.b) < EPS;
}

bool areParallel(line l1, line l2)  // Check coefficient a + b.
{
  return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

// True if two line segments are on the same line.
// Note that the line segments do not have to be the same for this to be true!
bool areSame(line l1, line l2)  // Check coefficients a + b + c.
{
  return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

// True if two lines meet at a right angle (90 degrees).
bool arePerpendicular(line l1, line l2)
{
  // Handle case of vertical and horizontal line.
  if ((isHorizontal(l1) && isVertical(l2)) || // l1 horizontal, l2 vertical
      (isHorizontal(l2) && isVertical(l1)))   // l2 horizontal, l1 vertical
  {
    return true;
  }
  return -(l1.a) * -(l2.a) == -1;
}

// Checks if two lines (not line segments) intersect.
// Returns true + intersection point if intersect.
bool areIntersect(line l1, line l2, point &p)
{
  if (areSame(l1, l2)) return false;  // All points intersect!
  if (areParallel(l1, l2)) return false;  // Parallel lines do not intersect!

  // Otherwise 2 lines intersect at some point (Note: lines, not line segments).
  // Solve system of 2 linear algebraic equations with 2 unknowns.
  p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  if (fabs(l1.b) > EPS)  // Special case: test (line 1) for vertical line.
    p.y = -(l1.a * p.x + l1.c);
  else  // l1.b and l2.b cannot be parallel (both 0) at this stage...
    p.y = -(l2.a * p.x + l2.c);
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
    x = p2.x - p1.x;
    y = p2.y - p1.y;
  }
};

// Returns a vector with its magnitude scaled by s.
// s < 1, shorter vector; s = 1, same vector; s > 1, longer vector
vec scaleVector(vec v, double s)
{
  return vec(v.x * s, v.y * s);
}

point translate(point p, vec v)  // Translate p according to v.
{
  return point(p.x + v.x, p.y + v.y);
}

// Returns the closest point (in ans, by reference) from point p to line l.
// Does the same as distToLine() but calculates it differently and it doesn't
// return the (Euclidean) distance from point p to the closest point,
// which you can easily get with dist(p, ans).
void closestPoint(line l, point p, point &ans)
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
  // Create a perpendicular (orthogonal) line using point p and slope. 
  line perpendicular(p, 1 / l.a);  // Perpendicular to l and pass through p.
  areIntersect(l, perpendicular, ans);  // Intersection point is closest point.
}

// The reflection of point on a (mirror) line.
void reflectionPoint(line l, point p, point &ans)
{
  point b(0.0, 0.0);
  closestPoint(l, p, b); // point to line
  vec v(p, b); // create a vector using the 2 points
  ans = translate(translate(p, v), v); // translate p twice
}

// Returns the dot product between two vectors.
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// Returns the distance from point p to the line AB (where A != B).
// Note that it's using the line, not the line segment!
// The closest point is also stored in point c, the 4th parameter, by reference.
double distToLine(point p, point A, point B, point &c)
{
  // formula: c = A + u * AB
  vec Ap(A, p), AB(A, B);
  double u = dot(Ap, AB) / norm_sq(AB);
  c = translate(A, scaleVector(AB, u));
  return dist(p, c);
}

// Similar to distToLine but uses a different formula (not preferred).
double distToLine2(point p, point A, point B, point &c)
{
  // formula: cp = A + (p-A).(B-A) / |B-A| * (B-A)
  double scale = (double)
    ((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y)) /
    ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
  c.x = A.x + scale * (B.x - A.x);
  c.y = A.y + scale * (B.y - A.y);
  return dist(p, c); // Euclidean distance between p and c.
}

// Returns the distance from point p to the line segment AB (OK if A == B).
// The closest point is stored in point c, the 4th parameter, by reference.
double distToLineSegment(point p, point A, point B, point &c)
{
  vec Ap(A, p), AB(A, B);
  double u = dot(Ap, AB) / norm_sq(AB);
  if (u < 0.0)
  {
    c = point(A.x, A.y); // closer to A
    return dist(p, A); // Euclidean distance between p and A
  } 
  if (u > 1.0)
  {
    c = point(B.x, B.y); // closer to B
    return dist(p, B); // Euclidean distance between p and B
  }
  return distToLine(p, A, B, c);
}

// Similar to distToLineSegment but uses a different formula (not preferred).
double distToLineSegment2(point p, point A, point B, point &c)
{
  if ((B.x - A.x) * (p.x - A.x) + (B.y - A.y) * (p.y - A.y) < EPS)
  {
    c.x = A.x;
    c.y = A.y; // closer to A
    return dist(p, A); // Euclidean distance between p and A
  }
  if ((A.x - B.x) * (p.x - B.x) + (A.y - B.y) * (p.y - B.y) < EPS)
  {
    c.x = B.x;
    c.y = B.y; // closer to B
    return dist(p, B); // Euclidean distance between p and B
  }
  return distToLine(p, A, B, c);
}

// Returns the angle aob in radians.
// Use RAD_to_DEG() to convert it to degrees.
double angle(point a, point o, point b)
{
  vec oa(o, a), ob(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

// Returns the cross product of 3 points.
double cross(point p0, point p1, point p2)
{
  return (p2.x - p1.x) * (p0.y - p1.y) - (p2.y - p1.y) * (p0.x - p1.x);
}

// Returns the cross product of 2 vectors.
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// Collinear (true) if p2 is on the line p0p1.
bool collinear(point p0, point p1, point p2)
{
  return fabs(cross(vec(p0, p1), vec(p0, p2))) < EPS;
}

// Similar to collinear but uses point arithmetic instead of vector arithmetic.
bool collinear2(point p0, point p1, point p2)
{
  return fabs(cross(p0, p1, p2)) < EPS;
}

// Counter-clock wise (true) if p2 is on the left of line p0p1.
bool ccw(point p0, point p1, point p2)
{
  return cross(vec(p0, p1), vec(p0, p2)) > 0; // Doesn't check for == 0.
}

// Similar to ccw but uses points arithmetic instead of vector arithmetic.
bool ccw2(point p0, point p1, point p2)
{
  return cross(p0, p1, p2) > 0;  // Doesn't check for == 0 (i.e. collinear).
}

bool nonLeftTurn(point p0, point p1, point p2)  // True if right turn or collinear.
{
  return !ccw(p0, p1, p2) || collinear(p0, p1, p2);
}

// AC_RUSH begin

// Returns the cross product given 3 point coordinates.
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
// Note that this does not give you the intersection point!
// FIXME: Fails its test!
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
