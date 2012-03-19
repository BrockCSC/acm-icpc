/* Forming Quiz Teams */

#include <algorithm>
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

#define MAX_BITMASK 65536 // this is 2^16, max N = 8

char line[1000], name[1000];
int i, j, N, x[20], y[20], caseNo = 1;
double dist[20][20], memo[65536];

double matching(int bitmask) {
  if (memo[bitmask] > -0.1) // we initialize the array with -1
    return memo[bitmask];

  if (bitmask == (int)(pow(2.0, 2.0 * N) - 1)) // all are matched
    return memo[bitmask] = 0;

  double matching_value = 32767 * 32767;
  for (int p1 = 0; p1 < 2 * N; p1++)
    if (!(bitmask & (1 << p1))) { // if this bit is off
      for (int p2 = p1 + 1; p2 < 2 * N; p2++)
        if (!(bitmask & (1 << p2))) // if this different bit is also off
          matching_value = min(matching_value, 
            dist[p1][p2] + matching(bitmask | (1 << p1) | (1 << p2)));
      break; // to improve the complexity from O(16^2 * 2^N) to O(16 * 2^N)
    }

  return memo[bitmask] = matching_value;
}

int main() {
  while (sscanf(gets(line), "%d", &N), N) {
    for (i = 0; i < 2 * N; i++)
      sscanf(gets(line), "%s %d %d", &name, &x[i], &y[i]);

    for (i = 0; i < 2 * N; i++)
      for (j = 0; j < 2 * N; j++)
        dist[i][j] = sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) + 
                                  (y[i] - y[j]) * (y[i] - y[j]));

    // using DP to solve matching on general graph
    memset(memo, -1, sizeof memo);
    printf("Case %d: %.2lf\n", caseNo++, matching(0));
  }

  return 0;
}
