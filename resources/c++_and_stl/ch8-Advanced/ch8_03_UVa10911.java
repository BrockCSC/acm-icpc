import java.util.*;
import java.text.*;

class Main { /* UVa 10911 - Forming Quiz Teams */
  private static int N, x[] = new int[20], y[] = new int[20], caseNo = 1;
  private static double dist[][] = new double[20][], memo[] = new double[65536]; // this is 2^16, max N = 8

  private static double matching(int bit_mask) {
    if (memo[bit_mask] > -0.1) // we initialize the array with -1
      return memo[bit_mask];

    if (bit_mask == (1 << (2 * N)) - 1) // all are matched
      return memo[bit_mask] = 0;

    double matching_value = 32767 * 32767;
    for (int p1 = 0; p1 < 2 * N; p1++)
      if (1 - (bit_mask & (1 << p1)) == 1) { // if this bit is off
        for (int p2 = p1 + 1; p2 < 2 * N; p2++)
          if (1 - (bit_mask & (1 << p2)) == 1) // if this different bit is also off
            matching_value = Math.min(matching_value, 
              dist[p1][p2] + matching(bit_mask | (1 << p1) | (1 << p2)));
        break; // to improve the complexity from O(16^2 * 2^N) to O(16 * 2^N)
      }

    return memo[bit_mask] = matching_value;
  }

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    while (true) {
      N = sc.nextInt();
      if (N == 0)
        break;

      for (int i = 0; i < 2 * N; i++) {
        String name = sc.next(); // dummy
        x[i] = sc.nextInt();
        y[i] = sc.nextInt();
      }

      for (int i = 0; i < 2 * N; i++) {
        dist[i] = new double[20];
        for (int j = 0; j < 2 * N; j++)
          dist[i][j] = Math.sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) + 
                                         (y[i] - y[j]) * (y[i] - y[j]));
      }

      // using DP to solve matching on general graph
      for (int i = 0; i < 65536; i++)
        memo[i] = -1.0;
      System.out.println(String.format("Case %d: %.2f", caseNo++, matching(0)));
    }
  }
}
