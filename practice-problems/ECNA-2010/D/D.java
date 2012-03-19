/* Solution to "Photo Shoot" */

import java.util.*;

class Pair implements Comparable<Pair> {
  public int x, y;
  public double angle;
  public Pair(int x, int y, double a) {
    this.x = x; this.y = y; this.angle = a;
  }
  public int compareTo(Pair p) {
    if (this.angle < p.angle) return -1;
    else if (this.angle > p.angle) return 1;
    else return 0;
  }
}

public class PhotoShoot {
  public static int n, ax, ay, f;
  public static int[] x, y;
  public static Scanner in;
  public static int caseNum;
  public static Pair angle[];

  public static void main(String[] args) {
    in = new Scanner(System.in);
    caseNum = 0;
    while (true) {
      n = in.nextInt();
      ax = in.nextInt();
      ay = in.nextInt();
      f = in.nextInt();
      if (n == 0) break;
      caseNum ++;
      x = new int[n];
      y = new int[n];
      for (int i = 0; i < n; i++) {
        x[i] = in.nextInt();
        y[i] = in.nextInt();
      }
      int min = solve();
      System.out.println("Case " + caseNum + ": " + min);
    }
  }

  public static int solve() {
    sortByAngle();
    int mincount = Integer.MAX_VALUE;
    // greedy, but depends on choice of starting position
    for (int i = 0; i < n; i++) {
      int k = group(i);
      if (k < mincount)
        mincount = k;
    }
    return mincount;
  }

  public static void sortByAngle() {
    angle = new Pair[n];
    for (int i = 0; i < n; i++) {
      int dx = x[i] - ax;
      int dy = y[i] - ay;
      double d = Math.sqrt(dx*dx+dy*dy); // d can't be zero
      angle[i] = new Pair(dx,dy,Math.acos(dx/d));
      if (dy < 0)
        angle[i].angle = 2*Math.PI - angle[i].angle;
    }
    Arrays.sort(angle);
    double field = f/360.0*2*Math.PI; // field = radian version of field of view
    for (int i = 0; i < n-1; i++) {
      for (int j = i+1; j < n-1; j++) {
         if (Math.abs(angle[j].angle-angle[i].angle - field) < 1E-3) {
           System.out.print("Warning -- angle difference very close to f = "+f);
           System.out.printf("(%d,%d) (%d,%d)\n",angle[i].x,angle[i].y,
                          angle[j].x,angle[j].y);
         }
      }
    }
  }

  public static int group(int start) {
    double field = f/360.0*2*Math.PI;
    int i = 0;
    double ang = angle[start].angle;
    int mincount = 1;
    while (i < n-1) {
      i++;
      start = (1+start)%n;
     
      double diff = angle[start].angle - ang;
      if (diff < 0)
        diff += 2*Math.PI;
      if (diff - field > 1e-5) {
        mincount++;
        ang = angle[start].angle;
      }
    }
    return mincount;
  }
}
