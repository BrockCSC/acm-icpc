/* Maximum Sum */

#include <iostream>
using namespace std;

#define REP(i, a, b) 	for (int i = int(a); i <= int(b); i++)

int main() { // O(n^4) DP solution
  int i, j, k, l, n, arr[101][101], maxSubRect, subRect;

  scanf("%d", &n);
  REP (i, 0, n - 1)
    REP (j, 0, n - 1) {
      scanf("%d", &arr[i][j]);
      if (i > 0) // 2nd row onwards
        arr[i][j] += arr[i - 1][j]; // add from top
      if (j > 0) // 2nd col onwards
        arr[i][j] += arr[i][j - 1]; // add form left
      if (i > 0 && j > 0)
        arr[i][j] -= arr[i - 1][j - 1]; // to avoid double count
    }

  maxSubRect = -127*100*100; // lowest possible value for this problem
  REP (i, 0, n - 1) REP (j, 0, n - 1)
    REP (k, i, n - 1) REP (l, j, n - 1) {
      subRect = arr[k][l];
      if (i > 0) subRect -= arr[i - 1][l];
      if (j > 0) subRect -= arr[k][j - 1];
      if (i > 0 && j > 0) subRect += arr[i - 1][j - 1];
      maxSubRect = max(maxSubRect, subRect);
    }

  printf("%d\n", maxSubRect);

  return 0;
}



/*
// brute force, TLE
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int n, arr[101][101], maxSubRect, subRect;

  scanf("%d", &n);
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    scanf("%d", &arr[i][j]);

  maxSubRect = -127*100*100; // lowest possible value for this problem
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) // start coord
    for  (int k = i; k < n; k++) for (int l = j; l < n; l++) { // end coord
      subRect = 0; // sum items in this sub-rectangle
      for (int a = i; a <= k; a++) for (int b = j; b <= l; b++)
        subRect += arr[a][b];
      maxSubRect = max(maxSubRect, subRect); // keep largest so far
    }

  printf("%d\n", maxSubRect);
}

*/



/*
#include <iostream>
using namespace std;

#define REP(i, a, b) 	for (int i = int(a); i <= int(b); i++)

int main() { // O(n^3) DP solution
  int n, unCounted = 1, currentMax = 0, possibleMax, matrix[101][101];

  scanf("%d", &n);
  REP (i, 0, n - 1)
    REP (j, 0, n - 1) {
      scanf("%d", &matrix[i][j]);
      if (j > 0) matrix[i][j] += matrix[i][j - 1]; // pre-processing
    }

  REP (left, 0, n - 1)
    REP (right, left, n - 1) {
      possibleMax = 0;
      REP (row, 0, n - 1) {
        if (left > 0)
          possibleMax += matrix[row][right] - matrix[row][left - 1];
        else
          possibleMax += matrix[row][right];
        
        if (possibleMax < 0) possibleMax = 0;

        if (unCounted || possibleMax > currentMax) {
          currentMax = possibleMax;
          unCounted = 0;
        }
      }
    }

  printf("%d\n", currentMax);
} // return 0;
*/
