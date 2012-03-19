#include <cstdio>
#include <cmath>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0)

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point_i { int x, y; // whenever possible, work with point_i
  point_i(int _x, int _y) { x = _x, y = _y; }
};
struct point { double x, y;
  point(double _x, double _y) { x = _x, y = _y; }
};

double dist(point p1, point p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y); }

double perimeter(double ab, double bc, double ca) {
  return ab + bc + ca; }

double perimeter(point a, point b, point c) {
  return dist(a, b) + dist(b, c) + dist(c, a); }

double area(double ab, double bc, double ca) {
  // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
  double s = 0.5 * perimeter(ab, bc, ca);
  return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca); }

double area(point a, point b, point c) {
  return area(dist(a, b), dist(b, c), dist(c, a)); }

double rInCircle(double ab, double bc, double ca) {
  return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

double rInCircle(point a, point b, point c) {
  return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

double rCircumCircle(double ab, double bc, double ca) {
  return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

double rCircumCircle(point a, point b, point c) {
  return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

bool canFormTriangle(double a, double b, double c) {
  return (a + b > c) && (a + c > b) && (b + c > a); }

// not tested yet
// circumcenter of circle through three points
int circle(point p1, point p2, point p3, point *ctr, double *r) {
  double a, b, c, d, e, f, g;
  a = p2.x - p1.x;
  b = p2.y - p1.y;
  c = p3.x - p1.x;
  d = p3.y - p1.y;
  e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
  if (fabs(g) < EPS)
    return 0;

  ctr->x = (d*e - b*f) / g;
  ctr->y = (a*f - c*e) / g;
  *r = sqrt((p1.x-ctr->x) * (p1.x-ctr->x) + (p1.y-ctr->y) * (p1.y-ctr->y));
  return 1;
}

int inCircle2(point p, point q, point r, point s) {
  return 0; // not yet implemented
}

int main() {
  double base = 4.0, h = 3.0;
  double A = 0.5 * base * h;
  printf("Area = %.2lf\n", A);

  point a(0.0, 0.0); // a right triangle
  point b(4.0, 0.0);
  point c(4.0, 3.0);

  double p = perimeter(a, b, c);
  double s = 0.5 * p;
  A = area(a, b, c);
  printf("Area = %.2lf\n", A); // must be the same as above

  printf("R1 (radius of inner circle) = %.2lf\n", rInCircle(a, b, c));
  printf("R2 (radius of outer circle) = %.2lf\n", rCircumCircle(a, b, c));

  // Law of Cosines
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  double alpha = RAD_to_DEG(acos((ca * ca + ab * ab - bc * bc) / (2.0 * ca * ab)));
  printf("alpha = %.2lf\n", alpha);
  double beta  = RAD_to_DEG(acos((ab * ab + bc * bc - ca * ca) / (2.0 * ab * bc)));
  printf("beta  = %.2lf\n", beta);
  double gamma = RAD_to_DEG(acos((bc * bc + ca * ca - ab * ab) / (2.0 * bc * ca)));
  printf("gamma = %.2lf\n", gamma);

  // Law of Sines
  printf("%.2lf == %.2lf == %.2lf\n", bc / sin(DEG_to_RAD(alpha)), ca / sin(DEG_to_RAD(beta)), ab / sin(DEG_to_RAD(gamma)));

  // Phytagorean Theorem
  printf("%.2lf^2 == %.2lf^2 + %.2lf^2\n", ca, ab, bc);

  // Triangle Inequality
  printf("(%d, %d, %d) => can form triangle? %d\n", 3, 4, 5, canFormTriangle(3, 4, 5)); // yes
  printf("(%d, %d, %d) => can form triangle? %d\n", 3, 4, 7, canFormTriangle(3, 4, 7)); // no, actually straight line
  printf("(%d, %d, %d) => can form triangle? %d\n", 3, 4, 8, canFormTriangle(3, 4, 8)); // no

  return 0;
}
