import java.util.*;

class Main { /* What Goes Up */
  // O(nk) LNIS DP (longest NON-increasing sequence)

  private static int upperbound(int[] A, int len, int key) {
    // please convert this code to binary search to achieve
    // O(log k) instead of O(k) performance :)

    int i;
    for (i = 0; i < len; i++) // O(k)
      if (A[i] < key)
        break;
    return i;
  }
  
  public static void main(String[] args) {
    final int MAX_N = 200000;
    int i, lnis = 0, n, caseNo = 1;
    int[] X = new int[MAX_N], A = new int[MAX_N];
    Boolean first = true;

    Scanner sc = new Scanner(System.in);
    while (true) {
      n = 0;
      while (true) { // read this test case
        X[n] = sc.nextInt();
        if (X[n] == -1) break;
        n++;
      }

      if (X[0] == -1) break; // end of input

      // O(n log k) algorithm
      for (A[0] = X[0], i = lnis = 1; i < n; i++) { // O(n)
        int l = upperbound(A, lnis, X[i]); // find insertion point, O(k)
        lnis = Math.max(lnis, l + 1);
        A[l] = X[i];
      }

      if (!first) System.out.printf("\n");
      first = false;
      System.out.printf("Test #%d:\n", caseNo++);
      System.out.printf("  maximum possible interceptions: %d\n", lnis);
    }
  }
}
