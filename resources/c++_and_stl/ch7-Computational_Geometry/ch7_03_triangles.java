import java.util.*;

class ch7_03_triangles {
  double DEG_to_RAD(double d) { return d * Math.PI / 180.0; }
  double RAD_to_DEG(double r) { return r * 180.0 / Math.PI; }

  class point_i {
    int x, y; // whenever possible, work with point_i
    point_i(int _x, int _y) { x = _x; y = _y; }
  };
  class point {
    double x, y;
    point(double _x, double _y) { x = _x; y = _y; }
  };

  double dist(point p1, point p2) {
    return Math.hypot(p1.x - p2.x, p1.y - p2.y); }

  double perimeter(double ab, double bc, double ca) {
    return ab + bc + ca; }

  double perimeter(point a, point b, point c) {
    return dist(a, b) + dist(b, c) + dist(c, a); }

  double area(double ab, double bc, double ca) {
    // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
    double s = 0.5 * perimeter(ab, bc, ca);
    return Math.sqrt(s) * Math.sqrt(s - ab) * Math.sqrt(s - bc) * Math.sqrt(s - ca); }

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

  boolean canFormTriangle(double a, double b, double c) {
    return (a + b > c) && (a + c > b) && (b + c > a); }

  // not tested yet
  // circumcenter of circle through three points
  double circle(point p1, point p2, point p3, point ctr) {
    double a, b, c, d, e, f, g;
    a = p2.x - p1.x;
    b = p2.y - p1.y;
    c = p3.x - p1.x;
    d = p3.y - p1.y;
    e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (Math.abs(g) < 1e-9)
      return 0;

    ctr.x = (d*e - b*f) / g;
    ctr.y = (a*f - c*e) / g;
    return Math.sqrt((p1.x-ctr.x) * (p1.x-ctr.x) + (p1.y-ctr.y) * (p1.y-ctr.y));
  }

  int inCircle2(point p, point q, point r, point s) {
    return 0; // not yet implemented
  }

  void run() {
    double base = 4.0, h = 3.0;
    double A = 0.5 * base * h;
    System.out.printf("Area = %.2f\n", A);

    point a = new point(0.0, 0.0); // a right triangle
    point b = new point(4.0, 0.0);
    point c = new point(4.0, 3.0);

    double p = perimeter(a, b, c);
    double s = 0.5 * p;
    A = area(a, b, c);
    System.out.printf("Area = %.2f\n", A); // must be the same as above

    System.out.printf("R1 (radius of inner circle) = %.2f\n", rInCircle(a, b, c));
    System.out.printf("R2 (radius of outer circle) = %.2f\n", rCircumCircle(a, b, c));

    // Law of Cosines
    double ab = dist(a, b);
    double bc = dist(b, c);
    double ca = dist(c, a);
    double alpha = RAD_to_DEG(Math.acos((ca * ca + ab * ab - bc * bc) / (2.0 * ca * ab)));
    System.out.printf("alpha = %.2f\n", alpha);
    double beta  = RAD_to_DEG(Math.acos((ab * ab + bc * bc - ca * ca) / (2.0 * ab * bc)));
    System.out.printf("beta  = %.2f\n", beta);
    double gamma = RAD_to_DEG(Math.acos((bc * bc + ca * ca - ab * ab) / (2.0 * bc * ca)));
    System.out.printf("gamma = %.2f\n", gamma);

    // Law of Sines
    System.out.printf("%.2f == %.2f == %.2f\n", 
      bc / Math.sin(DEG_to_RAD(alpha)),
      ca / Math.sin(DEG_to_RAD(beta)),
      ab / Math.sin(DEG_to_RAD(gamma)));

    // Phytagorean Theorem
    System.out.printf("%.2f^2 == %.2f^2 + %.2f^2\n", ca, ab, bc);

    // Triangle Inequality
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 5, canFormTriangle(3, 4, 5)); // yes
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 7, canFormTriangle(3, 4, 7)); // no, actually straight line
    System.out.printf("(%d, %d, %d) => can form triangle? %b\n", 3, 4, 8, canFormTriangle(3, 4, 8)); // no
  }

  public static void main(String[] args){
    new ch7_03_triangles().run();
  }
}
