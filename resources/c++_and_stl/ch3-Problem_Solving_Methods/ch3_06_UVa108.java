import java.util.*;

class Main { /* Maximum Sum */
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int i, j, left, right, row, n, unCounted = 1, currentMax = 0, possibleMax;
    int[][] matrix = new int[101][101];

    n = sc.nextInt();
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++) {
        matrix[i][j] = sc.nextInt();
        if (j > 0) matrix[i][j] += matrix[i][j - 1]; // pre-processing
      }

    // O(n^3) greedy solution (Kadane's algorithm)
    for (left = 0; left < n; left++)
      for (right = left; right < n; right++) {
        possibleMax = 0;
        for (row = 0; row < n; row++) {
          if (left > 0)
            possibleMax += matrix[row][right] - matrix[row][left - 1];
          else
            possibleMax += matrix[row][right];
        
          // crucial part, immediately reset if running sum is negative
          if (possibleMax < 0) possibleMax = 0;

          if (unCounted == 1 || possibleMax > currentMax) {
            currentMax = possibleMax;
            unCounted = 0;
          }
        }
      }

    System.out.printf("%d\n", currentMax);
  }
}
