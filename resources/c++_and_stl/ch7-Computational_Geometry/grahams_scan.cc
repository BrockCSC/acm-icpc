/* COSC 4P03: Advanced Algorithms
 * Dennis Ideler, March 2012
 */

#include "compgeo.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// TODO: use const where appropriate.
point pivot;

bool compare_angle(point p1, point p2)  // Comparison function for polar angle.
{
  if (collinear(pivot, p1, p2))
    return dist(pivot, p1) > dist(pivot, p2);  // Compare distance.

  double dx1 = p1.x - pivot.x;
  double dy1 = p1.y - pivot.y;
  double dx2 = p2.x - pivot.x;
  double dy2 = p2.y - pivot.y;
  // atan2 returns the arc tangent (angle of a right triangle) in radians.
  return (atan2(dy1, dx1) - atan2(dy2, dx2)) < 0;  // Compare angles.
} // TODO: can use cosine to be more efficient

// O(n log n) running time.
vector<point> GrahamsScan(vector<point> p)
{
  int n = static_cast<int>(p.size());

  if (n <= 3) return p;  // Trivial. Convex hull is original set of points.

  // Let p0 be the point with minimum y-coord, and leftmost in case of tie.
  int min = 0;
  for (int i = 1; i < n; ++i)
  {
    if (p[i].y < p[min].y || p[i].y == p[min].y && p[i].x < p[min].x)
      min = i;
  }
  swap(p[0], p[min]);
  pivot = p[0];

  // Sort points in increasing order by angle w.r.t. (x-axis of) pivot point.
  sort(++p.begin(), p.end(), compare_angle);  // Do not include p[0] in sort.

  // Add points that make a counterclockwise turn to the convex hull.
  vector<point> s;  // Emulate stack w/ vector. More convenient in this case.
  s.push_back(p[0]);  // Initial stack contains first 3 points: p0, p1, p2.
  s.push_back(p[1]);
  s.push_back(p[2]);

  for (int i = 3; i < n; ++i)
  {
    point top = s.back(); 
    point second_top = s[s.size()-2];
    printf("top: (%.2lf, %.2lf)\n2nd top: (%.2lf,%.2lf)\n",top.x,top.y,second_top.x,second_top.y);

    // Remove vertices from the stack if they're not in the convex hull.
    while (nonLeftTurn(second_top, top, p[i]))
    {
      printf("non-left turn! pop S\n\n");
      s.pop_back();
      top = s.back(); 
      second_top = s[s.size()-2];
      printf("new top: (%.2lf, %.2lf)\nnew 2nd top: (%.2lf,%.2lf)\n",top.x,top.y,second_top.x,second_top.y);
    }
    printf("push %d to S\n\n",i);
    s.push_back(p[i]);
  }
  return s;
}

int main(int argc, char* argv[])
{
  // TODO: OpenGL stuff
  vector<point> p;
  p.push_back(point(4, 2));
  p.push_back(point(2, 2));
  p.push_back(point(4, 3));
  p.push_back(point(3, 4));
  p.push_back(point(2, 4));
  p.push_back(point(6, 6));
  p.push_back(point(2, 6));
  p.push_back(point(6, 5));
  cout << "Points in G:" << endl;
  for (int i = 0; i < (int)p.size(); ++i)
    printf("(%.2lf, %.2lf)\n", p[i].x, p[i].y);
  cout << endl;
  vector<point> convex_hull = GrahamsScan(p);
  printf("|S| = %d\n",(int)convex_hull.size());
  for (int i = 0; i < (int)convex_hull.size(); ++i)
    printf("(%.2lf, %.2lf)\n", convex_hull[i].x, convex_hull[i].y);
}
