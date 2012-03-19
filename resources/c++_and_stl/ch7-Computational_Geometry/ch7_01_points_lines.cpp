#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

//struct point_i { int x, y; }; // basic raw form, minimalist mode
struct point_i { int x, y; // whenever possible, work with point_i
  point_i(int _x, int _y) { x = _x, y = _y; } // constructor (optional)
};
struct point { double x, y; // only used if more precision is needed
  point(double _x, double _y) { x = _x, y = _y; } // constructor
  bool operator < (point const &other) const { // override `less than' operator
    if (fabs(x - other.x) > EPS) // useful if we need to sort the points
      return x < other.x; // first criteria , by x-axis
    return y < other.y;   // second criteria, by y-axis
} };

bool areSame(point_i p1, point_i p2) { // integer version
  return p1.x == p2.x && p1.y == p2.y; } // precise comparison

bool areSame(point p1, point p2) { // floating point version
  // use EPS when testing equality of two floating points
  return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS; }

double dist(point p1, point p2) { // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
  return hypot(p1.x - p2.x, p1.y - p2.y); } // return double

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
  // rotation matrix R(theta) = [cos(theta) -sin(theta)]
  //                            [sin(theta)  cos(theta)]
  double rad = DEG_to_RAD(theta); // must work in radian
  return point(p.x * cos(rad) - p.y * sin(rad),
               p.x * sin(rad) + p.y * cos(rad)); }

struct line { double a, b, c; }; // a way to represent a line

// the answer is stored in the third parameter (pass byref)
void pointsToLine(point p1, point p2, line *l) {
  if (p1.x == p2.x) { // vertical line is handled nicely here
    l->a = 1.0;   l->b = 0.0;   l->c = -p1.x;
  } else {
    l->a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
    l->b = 1.0;
    l->c = -(double)(l->a * p1.x) - (l->b * p1.y);
} }

// not needed since we will use the more robust form: ax + by + c = 0 (see above)
//struct line2 { double m, c; }; // another way to represent a line
//
//int pointsToLine(point p1, point p2, line2 *l) {
//  if (p1.x == p2.x) { // special case: vertical line
//    l->m = INF; // l contains m = INF and c = x_value
//    l->c = p1.x; // to denote vertical line x = x_value
//    return 0; // we need this return variable to differentiate result
//  }
//  else {
//    l->m = (double)(p1.y - p2.y) / (p1.x - p2.x);
//    l->c = p1.y - l->m * p1.x;
//    return 1; // l contains m and c of the line equation y = mx + c
//} }

bool areParallel(line l1, line l2) { // check coefficient a + b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) { // also check coefficient c
  return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point *p) {
  if (areSame(l1, l2)) return false; // all points intersect
  if (areParallel(l1, l2)) return false; // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p->x = (double)(l2.b * l1.c - l1.b * l2.c) / 
                 (l2.a * l1.b - l1.a * l2.b);
  if (fabs(l1.b) > EPS) // test for vertical line
    p->y = - (l1.a * p->x + l1.c) / l1.b; // avoid div by zero
  else // this is another special case in geometry problem...
    p->y = - (l2.a * p->x + l2.c) / l2.b;
  return true; }

struct vec { double x, y; // similar to point
  vec(double _x, double _y) { x = _x, y = _y; } };

vec toVector(point p1, point p2) { // convert 2 points to vector
  return vec(p2.x - p1.x, p2.y - p1.y); }

vec scaleVector(vec v, double s) { // s = [<1 ...   1   ... >1]
  return vec(v.x * s, v.y * s); }  // shorter v  same v  longer v

point translate(point p, vec v) { // translate p according to v
  return point(p.x + v.x , p.y + v.y); }

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line *l) {
  l->a = -m; // always -m
  l->b = 1;  // always 1
  l->c = -((l->a * p.x) + (l->b * p.y)); } // compute this

void closestPoint(line l, point p, point *ans) {
  line perpendicular; // perpendicular to l and pass through p
  if (fabs(l.b) < EPS) { // special case 1: vertical line
    ans->x = -(l.c);   ans->y = p.y;      return; }

  if (fabs(l.a) < EPS) { // special case 2: horizontal line
    ans->x = p.x;      ans->y = -(l.c);   return; }

  pointSlopeToLine(p, 1 / l.a, &perpendicular); // normal line
  // intersect line l with this perpendicular line
  // the intersection point is the closest point
  areIntersect(l, perpendicular, ans); }

// returns the distance from p to the line defined by
// two points A and B (A and B must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point A, point B, point *c) {
  // formula: cp = A + (p-A).(B-A) / |B-A| * (B-A)
  double scale = (double)
    ((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y)) /
    ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
  c->x = A.x + scale * (B.x - A.x);
  c->y = A.y + scale * (B.y - A.y);
  return dist(p, *c); } // Euclidean distance between p and *c

// returns the distance from p to the line segment ab defined by
// two points A and B (still OK if A == B)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point A, point B, point* c) {
  if ((B.x-A.x) * (p.x-A.x) + (B.y-A.y) * (p.y-A.y) < EPS) {
    c->x = A.x;   c->y = A.y; // closer to A
    return dist(p, A); } // Euclidean distance between p and A
  if ((A.x-B.x) * (p.x-B.x) + (A.y-B.y) * (p.y-B.y) < EPS) {
    c->x = B.x;   c->y = B.y; // closer to B
    return dist(p, B); } // Euclidean distance between p and B
  return distToLine(p, A, B, c); } // run distToLine as above

double cross(point p, point q, point r) { // cross product
  return (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x); }

//// another variant
//int area2(point p, point q, point r) { // returns 'twice' the area of this triangle A-B-c
//  return p.x * q.y - p.y * q.x +
//         q.x * r.y - q.y * r.x +
//         r.x * p.y - r.y * p.x;
//}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) { 
  return cross(p, q, r) > 0; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(p, q, r)) < EPS; }

int main() {
  vector<point> P;
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));

  /*
  // the positions of these 5 points (0-based indexing)
  6   P4      P3
  5           P5
  4   P2
  3       P1
  2   P0
  1
  0 1 2 3 4 5 6 
  */

  double d = dist(P[0], P[5]);
  printf("Euclidean distance between P[0] and P[5] = %.2lf\n", d); // should be 5.000

  // line equations
  line l1, l2, l3, l4;

  pointsToLine(P[0], P[1], &l1);
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l1.a, l1.b, l1.c); // should be -0.50 * x + 1.00 * y - 1.00 = 0.00

  pointsToLine(P[0], P[2], &l2); // a vertical line, not a problem in "ax + by + c = 0" representation
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 * x + 0.00 * y - 2.00 = 0.00

  // tests
  pointsToLine(P[2], P[3], &l3);
  printf("l1 & l2 are parallel? %d\n", areParallel(l1, l2)); // no
  printf("l1 & l3 are parallel? %d\n", areParallel(l1, l3)); // yes, l1 (P[0]-P[1]) and l3 (P[2]-P[3]) are parallel

  pointsToLine(P[2], P[4], &l4);
  printf("l1 & l2 are the same? %d\n", areSame(l1, l2)); // no
  printf("l2 & l4 are the same? %d\n", areSame(l2, l4)); // yes, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are the same line (note, they are two different line segments, but same line)

  point p12(0.0, 0.0);
  bool res = areIntersect(l1, l2, &p12); // yes, l1 (P[0]-P[1]) and l2 (P[0]-P[2]) are intersect at (2.0, 2.0)
  printf("l1 & l2 are intersect? %d, at (%.2lf, %.2lf)\n", res, p12.x, p12.y);

  // other distances
  point p023(0.0, 0.0);
  d = distToLine(P[0], P[2], P[3], &p023);
  printf("Closest point from P[0] to line         (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", p023.x, p023.y, d);
  point ans(0.0, 0.0);
  closestPoint(l3, P[0], &ans);
  printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, dist(P[0], ans));
  d = distToLineSegment(P[0], P[2], P[3], &p023);
  printf("Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", p023.x, p023.y, d);

  printf("P[0], P[2], P[3] are collinear? %d\n", collinear(P[0], P[2], P[3])); // no
  printf("P[0], P[2], P[4] are collinear? %d\n", collinear(P[0], P[2], P[4])); // yes

  printf("P[0], P[2], P[3] form A left turn? %d\n", ccw(P[0], P[2], P[3])); // no
  printf("P[0], P[3], P[2] form A left turn? %d\n", ccw(P[0], P[3], P[2])); // yes

  // example of sorting points based on its x-coordinate (then if tie, by its y-coordinate)
  sort(P.begin(), P.end()); // comparison operator is already defined
  for (int i = 0; i < (int)P.size(); i++)
    printf("(%.2lf, %.2lf)\n", P[i].x, P[i].y);

  /*
  // the positions of these 6 points
     E<--  4
           3       B D<--
           2   A C
           1
  -4-3-2-1 0 1 2 3 4 5 6 
          -1
          -2
   F<--   -3
  */

  // translation
  point A(2.0, 2.0);
  point B(4.0, 3.0);
  vec v = toVector(A, B); // imagine there is an arrow from A to B (see the diagram above)
  point C(3.0, 2.0);
  point D = translate(C, v); // D will be located in coordinate (3.0 + 2.0, 2.0 + 1.0) = (5.0, 3.0)
  printf("D = (%.2lf, %.2lf)\n", D.x, D.y);
  point E = translate(C, scaleVector(v, 0.5)); // E will be located in coordinate (3.0 + 1/2 * 2.0, 2.0 + 1/2 * 1.0) = (4.0, 2.5)
  printf("E = (%.2lf, %.2lf)\n", E.x, E.y);

  // rotation
  printf("B = (%.2lf, %.2lf)\n", B.x, B.y); // B = (4.0, 3.0)
  point F = rotate(B, 90); // rotate B by 90 degrees COUNTER clockwise, F = (-3.0, 4.0)
  printf("F = (%.2lf, %.2lf)\n", F.x, F.y);
  point G = rotate(B, 180); // rotate B by 180 degrees COUNTER clockwise, G = (-4.0, -3.0)
  printf("G = (%.2lf, %.2lf)\n", G.x, G.y);

  return 0;
}
