#include <algorithm>
#include <cstdio>
#include <cmath>
#include <stack>
#include <vector>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0)

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { double x, y; // we use double for most examples in this source code
  point(double _x, double _y) { x = _x, y = _y; } };

double dist(point p1, point p2) { // get Euclidean distance of two points
  return hypot(p1.x - p2.x, p1.y - p2.y); } // as shown earlier

// returns the perimeter of polygon, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(vector<point> P) {
  double result = 0.0;
  for (int i = 0; i < (int)P.size(); i++)
    result += dist(P[i], P[(i + 1) % P.size()]);
  return result; }

// returns the area, which is half the determinant
double area(vector<point> P) {
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size(); i++) {
    x1 = P[i].x; x2 = P[(i + 1) % P.size()].x;
    y1 = P[i].y; y2 = P[(i + 1) % P.size()].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2.0; }

double cross(point p, point q, point r) {
  return (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x); }

bool collinear(point p, point q, point r) {
  return fabs(cross(p, q, r)) < EPS; }

bool ccw(point p, point q, point r) {
  return cross(p, q, r) > 0; }

// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool isConvex(vector<point> P) {
  int sz = (int)P.size();
  if (sz < 3) // boundary case, we treat point/line as not convex
    return false;
  bool isLeft = ccw(P[0], P[1], P[2]); // remember one
  for (int i = 1; i < sz; i++) // compare with others
    if (ccw(P[i], P[(i + 1) % sz], P[(i + 2) % sz]) != isLeft)
      return false; // if different sign->this polygon is concave
  return true; } // this polygon is convex

double angle(point a, point b, point c) {
  double ux = b.x - a.x, uy = b.y - a.y;
  double vx = c.x - a.x, vy = c.y - a.y;
  return acos((ux*vx + uy*vy) / 
              sqrt((ux*ux + uy*uy) * (vx*vx + vy*vy))); }

// returns true if point p is in either convex/concave polygon P
bool inPolygon(point p, vector<point> P) {
  if ((int)P.size() == 0) return false;
  double sum = 0;
  for (int i = 0; i < (int)P.size() - 1; i++) {
    if (cross(p, P[i], P[i + 1]) < 0) // right turn/cw
         sum -= angle(p, P[i], P[i + 1]);
    else sum += angle(p, P[i], P[i + 1]); } // left turn/ccw
  return (fabs(sum - 2*PI) < EPS || fabs(sum + 2*PI) < EPS); }

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u + v),
               (p.y * v + q.y * u) / (u + v)); }

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, vector<point> Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
    double left1 = cross(a, b, Q[i]), left2 = 0.0;
    if (i != (int)Q.size() - 1) left2 = cross(a, b, Q[i + 1]);
    if (left1 > -EPS) P.push_back(Q[i]);
    if (left1 * left2 < -EPS)
      P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
  }
  if (P.empty()) return P;
  if (fabs(P.back().x - P.front().x) > EPS ||
      fabs(P.back().y - P.front().y) > EPS)
    P.push_back(P.front());
  return P; }

// Implementation of Graham's Scan (pg 191).

point pivot(0, 0);
bool angle_cmp(point a, point b) { // angle-sorting function
  if (collinear(pivot, a, b))
    return dist(pivot, a) < dist(pivot, b); // which one is closer?
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }

vector<point> CH(vector<point> P) {
  int i, N = (int)P.size();
  if (N <= 3) return P; // special case, the CH is P itself

  // first, find P0 = point with lowest Y and if tie: rightmost X
  int P0 = 0;
  for (i = 1; i < N; i++)
    if (P[i].y  < P[P0].y ||
       (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;
  // swap selected vertex with P[0]
  point temp = P[0]; P[0] = P[P0]; P[P0] = temp;

  // second, sort points by angle w.r.t. P0, skipping P[0]
  pivot = P[0]; // use this global variable as reference
  sort(++P.begin(), P.end(), angle_cmp);

  // third, the ccw tests
  point prev(0, 0), now(0, 0);
  stack<point> S; S.push(P[N - 1]); S.push(P[0]); //S.push(P[1]); // initial
  i = 1; // and start checking the rest
  while (i < N) { // note: N must be >= 3 for this method to work
    now = S.top();
    S.pop();
    prev = S.top();
    S.push(now); // get 2nd from top
    if (ccw(prev, now, P[i])) S.push(P[i++]); // left turn, ACC
    else S.pop(); // otherwise, pop until we have a left turn
  }

  vector<point> ConvexHull; // from stack back to vector
  while (!S.empty()) { ConvexHull.push_back(S.top()); S.pop(); }
  return ConvexHull; } // return the result

int main() {
  // 6 points, entered in counter clockwise order, 0-based indexing
  vector<point> P;                  //7 P5--------------P4
  P.push_back(point(1, 1));         //6 |                  \ 
  P.push_back(point(3, 3));         //5 |                    \ 
  P.push_back(point(9, 1));         //4 |                     P3
  P.push_back(point(12, 4));        //3 |   P1___            /
  P.push_back(point(9, 7));         //2 | /       \ ___    /
  P.push_back(point(1, 7));         //1 P0              P2
  P.push_back(P[0]); // loop back   //0 1 2 3 4 5 6 7 8 9 101112

  printf("Perimeter of polygon = %.2lf\n", perimeter(P)); // 31.64
  printf("Area of polygon = %.2lf\n", area(P)); // 49.00
  printf("Is convex = %d\n", isConvex(P)); // false (P1 is the culprit)

  //// the positions of P6 and P7 w.r.t the polygon
  //7 P5--------------P4
  //6 |                  \
  //5 |                    \
  //4 |   P7                P3
  //3 |   P1___            /
  //2 | / P6    \ ___    /
  //1 P0              P2
  //0 1 2 3 4 5 6 7 8 9 101112

  point P6(3, 2); // outside this (concave) polygon
  printf("Point P6 is inside this polygon = %d\n", inPolygon(P6, P)); // false
  point P7(3, 4); // inside this (concave) polygon
  printf("Point P7 is inside this polygon = %d\n", inPolygon(P7, P)); // true

  // cutting the original polygon based on line P[2] -> P[4] (get the left side)
  //7 P5--------------P4
  //6 |               |  \
  //5 |               |    \
  //4 |               |     P3
  //3 |   P1___       |    /
  //2 | /       \ ___ |  /
  //1 P0              P2
  //0 1 2 3 4 5 6 7 8 9 101112
  // new polygon (notice the index are different now):
  //7 P4--------------P3
  //6 |               |
  //5 |               |
  //4 |               |
  //3 |   P1___       |
  //2 | /       \ ___ |
  //1 P0              P2
  //0 1 2 3 4 5 6 7 8 9

  P = cutPolygon(P[2], P[4], P);
  printf("Perimeter of polygon = %.2lf\n", perimeter(P)); // smaller now 29.15
  printf("Area of polygon = %.2lf\n", area(P)); // 40.00

  // running convex hull of the resulting polygon (index changes again)
  //7 P3--------------P2
  //6 |               |
  //5 |               |
  //4 |   P7          |
  //3 |               |
  //2 |               |
  //1 P0--------------P1
  //0 1 2 3 4 5 6 7 8 9
  P = CH(P); // now this is a rectangle
  printf("Perimeter of polygon = %.2lf\n", perimeter(P)); // precisely 28.00
  printf("Area of polygon = %.2lf\n", area(P)); // precisely 48.00
  printf("Is convex = %d\n", isConvex(P)); // true
  printf("Point P7 is inside this polygon = %d\n", inPolygon(P7, P)); // true

  return 0;
}
