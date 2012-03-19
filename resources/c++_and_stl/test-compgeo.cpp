#include "compgeo.h" 
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  std::cout << dist(point(2.0, 2.0), point(6.0, 5.0)) << std::endl;
  std::cout << dist(2.0, 2.0, 6.0, 5.0) << std::endl;
  std::cout << distR(2.0, 2.0, 6.0, 5.0) << std::endl;

  line l1(point(2.0,2.0), point(4.0,3.0));
  line l2(2,2,2,5);
  printf("a = %f, b = %f, c = %f\n", l1.a, l1.b, l1.c);
  printf("a = %f, b = %f, c = %f\n", l2.a, l2.b, l2.c);
  std::cout << areSame(l1, l2) << std::endl;

  std::cout << cross(2,2,4,3,6,5) << std::endl;
  std::cout << cross(point(2,2),point(4,3),point(6,5)) << std::endl;
  std::cout << ccw(point(2,2),point(4,3),point(6,5)) << std::endl;
  std::cout << crossOper(2,2,4,3,6,5) << std::endl;

  vector<point> P;
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));
 
  // Sorting points demo.
  sort(P.begin(), P.end());
  for (int i = 0; i < (int)P.size(); i++)
    printf("(%.2lf, %.2lf)\n", P[i].x, P[i].y);

  // Rearrange points.
  P.clear();
  P.push_back(point(2, 2));
  P.push_back(point(4, 3));
  P.push_back(point(2, 4));
  P.push_back(point(6, 6));
  P.push_back(point(2, 6));
  P.push_back(point(6, 5));

  line l3(P[2], P[3]);
  point ans;
  closestPoint(l3, P[0], ans);
  printf("Closest point from P[0] to line V2      (P[2]-P[3]): (%.2lf, %.2lf), dist = %.2lf\n", ans.x, ans.y, dist(P[0], ans));
  
  printf("P[0], P[2], P[3] are collinear? %d\n", collinear(P[0], P[2], P[3])); // no
  printf("P[0], P[2], P[4] are collinear? %d\n", collinear(P[0], P[2], P[4])); // yes

  printf("P[0], P[2], P[3] form A left turn? %d\n", ccw(P[0], P[2], P[3])); // no
  printf("P[0], P[3], P[2] form A left turn? %d\n", ccw(P[0], P[3], P[2])); // yes
}
