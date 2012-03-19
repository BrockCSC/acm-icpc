/* Pseudo-Random Numbers */

import java.util.*;

class ch5_06_UVa530 {
  static int Z, I, M, L, mu, lambda;

  static int f(int x) { return (Z * x + I) % M; }

  static void floydCycleFinding(int x0) { // function "int f(int x)" must be defined earlier
    // 1st part: finding v, hare's speed is 2x tortoise's
    int tortoise = f(x0), hare = f(f(x0)); // f(x0) is the element/node next to x0
    while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
    // 2nd part: finding mu, hare and tortoise move at the same speed
    mu = 0; hare = x0;
    while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); mu++; }
    // 3rd part: finding lambda, hare moves, tortoise stays
    lambda = 1; hare = f(tortoise);
    while (tortoise != hare) { hare = f(hare); lambda++; }
  }

  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    for (int caseNo = 1; ; caseNo++) {
      Z = scan.nextInt();
      I = scan.nextInt();
      M = scan.nextInt();
      L = scan.nextInt();
      if (Z==0 && I==0 && M==0 && L==0) break;
      floydCycleFinding(L);
      System.out.printf("Case %d: %d\n", caseNo, lambda);
    }
  }
}
