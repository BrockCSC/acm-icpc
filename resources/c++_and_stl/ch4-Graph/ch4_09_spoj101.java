import java.util.Scanner;

public class ch4_09_spoj101 { /* SPOJ 101 - Fishmonger */
  static final int MAX_N = 55;
  static final int MAX_T = 1005;
  static final int INF = 2000000000;

  static int i, j, n, t;
  static int[][] toll = new int[MAX_N][MAX_N];
  static int[][] travelTime = new int[MAX_N][MAX_N];
  static IntegerPair[][] memo = new IntegerPair[MAX_N][MAX_T];

  static IntegerPair go(int cur, int t_left) { // top-down DP, returns a pair
    if (t_left < 0) return new IntegerPair(INF, INF); // invalid state
    if (cur == n - 1) return new IntegerPair(0, 0); // at last city, no need to pay toll and time needed is 0
    if (memo[cur][t_left].first() != -1) return memo[cur][t_left]; // visited before
    IntegerPair ans = new IntegerPair(INF, INF);
    for (int nxt = 0; nxt < n; nxt++) if (cur != nxt) { // try to go to another city
      IntegerPair nextCity = go(nxt, t_left - travelTime[cur][nxt]); // recursive step
      if (nextCity.first() + toll[cur][nxt] < ans.first()) { // pick the one that has min cost
        ans = new IntegerPair(nextCity.first()  + toll[cur][nxt],
                              nextCity.second() + travelTime[cur][nxt]);
    } }
    return memo[cur][t_left] = ans;
  } // store the answer to memo table as well as returning the answer to the caller


  public static void main(String[] args) {
    /*
    // sample input
    4 7
    0 5 2 3
    5 0 2 3
    3 1 0 2
    3 3 2 0

    0 2 2 7
    2 0 1 2
    2 2 0 5
    7 2 5 0

    0 0

    // sample output
    6 6
    */

    Scanner sc = new Scanner(System.in);
    while (true) {
      n = sc.nextInt(); t = sc.nextInt();
      if (n == 0 && t == 0)
        break;

      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
          travelTime[i][j] = sc.nextInt();

      for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
          toll[i][j] = sc.nextInt();

      for (i = 0; i <= n; i++)
        for (j = 0; j <= t; j++)
          memo[i][j] = new IntegerPair(-1, -1);

      IntegerPair res = go(0, t);
      System.out.printf("%d %d\n", res.first(), res.second());
    }
  }
}
