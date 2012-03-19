/* Modular Fibonacci */

import java.util.*;

class Main {
  static int i, n, m, MAX_N = 2;
  static long MOD;

  static long[][] matMul(long[][] a, long[][] b) {    // O(n^3 ~> 1) as n=2
    long[][] ans = new long[2][2]; int i, j, k;
    for (i = 0; i < MAX_N; i++)
      for (j = 0; j < MAX_N; j++)
        for (ans[i][j] = k = 0; k < MAX_N; k++) {
          ans[i][j] += (a[i][k] % MOD) * (b[k][j] % MOD);
          ans[i][j] %= MOD;               // modulo arithmetic is used here
        }
    return ans;
  }

  static long[][] matPow(long[][] base, int p) {   // O(n^3 log p ~> log p)
    long[][] ans = new long[MAX_N][MAX_N]; int i, j;
    for (i = 0; i < MAX_N; i++)
      for (j = 0; j < MAX_N; j++)
        ans[i][j] = (i == j ? 1 : 0);            // prepare identity matrix
    while (p > 0) { // iterative version of Divide & Conquer exponentiation
      if ((p & 1) == 1)           // check if p is odd (the last bit is on)
        ans = matMul(ans, base);                              // update ans
      base = matMul(base, base);                         // square the base
      p >>= 1;                                             // divide p by 2
    }
    return ans;
  }

  static int normalExp(int base, int p) {      // we just use int data type
    int ans = 1;
    for (int i = 0; i < p; i++) ans *= base;                        // O(p)
    return ans; }

  static int fastExp(int base, int p) {                         // O(log p)
         if (p == 0) return 1;
    else if (p == 1) return base;
    else {           int res = fastExp(base, p / 2); res *= res;
                     if (p % 2 == 1) res *= base;
                     return res; } }

  public static void main(String[] args) {
    // just for illustration (not part of UVa 10229 solution), uncomment to compare
    // System.out.printf("%d vs %d\n", normalExp(2, 4), fastExp(2, 4));
    // System.out.printf("%d vs %d\n", normalExp(2, 9), fastExp(2, 9));
    // System.out.printf("%d vs %d\n", normalExp(2, 22), fastExp(2, 22));

    Scanner sc = new Scanner(System.in);
    while (sc.hasNext()) {
      n = sc.nextInt(); m = sc.nextInt();

      for (MOD = 1, i = 0; i < m; i++)                     // set MOD = 2^m
        MOD *= 2;

      long[][] ans = new long[MAX_N][MAX_N];   // special Fibonaccci matrix
      ans[0][0] = 1;  ans[0][1] = 1;
      ans[1][0] = 1;  ans[1][1] = 0;

      ans = matPow(ans, n);                                     // O(log n)
      System.out.println(ans[0][1]);                      // this if fib(n)
    }
  }
}
