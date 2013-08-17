#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#include "geometry.h"

// TODO: assert test results
// TODO: write more tests, especially for AC_RUSH's stuff.

int main()
{
  vector<point> P;
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));
  P.push_back(point(8, 6));
  P.push_back(point(1, 3));

  // sorting points based on x-coordinate (then if tie, by y-coordinate)
  sort(P.begin(), P.end()); // comparison operator overloaded in point struct.
  for (int i = 0; i < (int)P.size(); i++)
    printf("(%.2lf, %.2lf)\n", P[i].x, P[i].y);

  // rearrange the points as shown in the diagram below
  P.clear();
  P.push_back(point(2, 2)); // P0
  P.push_back(point(4, 3)); // P1
  P.push_back(point(2, 4)); // P2
  P.push_back(point(6, 6)); // P3
  P.push_back(point(2, 6)); // P4
  P.push_back(point(6, 5)); // P5
  P.push_back(point(8, 6)); // P6
  P.push_back(point(1, 3)); // P7
  P.push_back(point(0, 1)); // P8
  P.push_back(point(3, 7)); // P9
  P.push_back(point(0, 4)); // P10
  P.push_back(point(8, 0)); // P11
  P.push_back(point(1, 2)); // P12
  P.push_back(point(3, 2)); // P13
  
  /*                                      
 (y)                                       
  7               P9                      7
  6           P4              P3      P6  6
  5                           P5          5
  4   P10     P2                          4
  3       P7          P1                  3
  2       P12 P0  P13                     2
  1   P8                                  1
  0                                   P11 0
 -1   0   1   2   3   4   5   6   7   8   9 (x)
  */

  double d = dist(P[0], P[5]);
  printf("Euclidean distance between P[0] and P[5] = %.2lf\n", d); // should be 5.000

  // line equations
  line l1(P[0], P[1]);
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l1.a, l1.b, l1.c); // should be -0.50 * x + 1.00 * y - 1.00 = 0.00

  line l2(P[0], P[2]); // a vertical line, not a problem in "ax + by + c = 0" representation
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 * x + 0.00 * y - 2.00 = 0.00

  line l3(P[2], P[3]);
  printf("l1 & l2 are parallel? %d\n", areParallel(l1, l2)); // no
  printf("l2 & l2 are parallel? %d\n", areParallel(l2, l2)); // yes
  printf("l1 & l3 are parallel? %d\n", areParallel(l1, l3)); // yes, l1 (P[0]-P[1]) and l3 (P[2]-P[3]) are parallel

  line l4(P[2], P[4]);
  printf("l1 & l2 are the same? %d\n", areSame(l1, l2)); // no
  printf("l2 & l2 are the same? %d\n", areSame(l2, l2)); // yes
  printf("l2 & l4 are the same? %d\n", areSame(l2, l4)); // yes, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are the same line (note, they are two different line segments, but same line)

  line l5(P[7], P[1]);
  line l6(P[0], P[5]);
  line l7(P[8], P[9]);
  line l8(P[10], P[11]);
  printf("l3 and l5 are perpendicular? %d\n", arePerpendicular(l3, l5)); // no, don't even intersect
  printf("l5 and l6 are perpendicular? %d\n", arePerpendicular(l5, l6)); // no
  printf("l2 and l5 are perpendicular? %d\n", arePerpendicular(l2, l5)); // yes, vertical line and a horizontal line
  printf("l7 and l8 are perpendicular? %d\n", arePerpendicular(l7, l8)); // yes, meet at a right angle

  point ans(0.0, 0.0);
  bool res = areIntersect(l1, l2, ans); // yes, l1 (P[0]-P[1]) and l2 (P[0]-P[2]) are intersect at (2.0, 2.0)
  printf("l1 & l2 are intersect? %d, at (%.2lf, %.2lf)\n", res, ans.x, ans.y);
  ans = (0, 0);
  res = areIntersect(l2, l4, ans); // no, l2 (P[0]-P[2]) and l4 (P[2]-P[4]) are on the same line, intersects at every point
  printf("l2 & l4 are intersect? %d, at (%.2lf, %.2lf)\n", res, ans.x, ans.y);
  ans = (0, 0);
  line l9(P[12], P[13]);
  res = areIntersect(l2, l9, ans); // yes, l2 (P[0]-P[2]) and l9 (P[12]-P[13]) intersect at (2, 2)
  printf("l2 & l9 are intersect? %d, at (%.2lf, %.2lf)\n", res, ans.x, ans.y);
  ans = (0, 0);
  // Test AC_RUSH's isIntersect(x1, y1, x2, y2, x3, y3, x4, y4) -> bool
  res = isIntersect(P[0].x, P[0].y, P[1].x, P[1].y, P[0].x, P[0].y, P[2].x, P[2].y);
  printf("l1 & l2 are intersect (using isIntersect)? %d\n", res); // FIXME

  // other distances
  d = distToLine(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line         (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d);
  d = distToLine2(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d);
  closestPoint(l3, P[0], ans);
  printf("Closest point from P[0] to line V3      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, dist(P[0], ans));

  d = distToLineSegment(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to A (or P[2]) = (2.00, 4.00)
  d = distToLineSegment2(P[0], P[2], P[3], ans);
  printf("Closest point from P[0] to line SEGMENT2(P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to A (or P[2]) = (2.00, 4.00)
  d = distToLineSegment(P[1], P[2], P[3], ans);
  printf("Closest point from P[1] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to midway between AB = (3.20, 4.60)
  d = distToLineSegment(P[6], P[2], P[3], ans);
  printf("Closest point from P[6] to line SEGMENT (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, d); // closer to B (or P[3]) = (6.00, 6.00)

  reflectionPoint(l4, P[1], ans);
  printf("Reflection point from P[1] to line      (P[2]-P[4]): (%.2lf, %.2lf)\n", ans.x, ans.y); // should be (0.00, 3.00)

  printf("Angle P[0]-P[4]-P[3] = %.2lf\n", RAD_to_DEG(angle(P[0], P[4], P[3]))); // 90 degrees
  printf("Angle P[0]-P[2]-P[1] = %.2lf\n", RAD_to_DEG(angle(P[0], P[2], P[1]))); // 63.43 degrees
  printf("Angle P[4]-P[3]-P[6] = %.2lf\n", RAD_to_DEG(angle(P[4], P[3], P[6]))); // 180 degrees

  printf("P[0], P[2], P[3] are collinear? %d\n", collinear(P[0], P[2], P[3])); // no
  printf("P[0], P[2], P[4] are collinear? %d\n", collinear(P[0], P[2], P[4])); // yes

  printf("P[0], P[2], P[3] form a left turn? %d\n", ccw(P[0], P[2], P[3])); // no
  printf("P[0], P[3], P[2] form a left turn? %d\n", ccw(P[0], P[3], P[2])); // yes
  
  // TODO: test AC_RUSH's crossOper(x0, y0, x1, y1, x2, y2) -> int
  //       > 0 : counterclockwise from p0p1 to p1p2
  //       < 0 : clockwise from p0p1 to p1p2
  //       = 0 : p0p1p2 are collinear


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
  vec v(A, B); // imagine there is an arrow from A to B (see the diagram above)
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
}
