/* SPOJ 101 - Fishmonger */

#include <algorithm>
#include <iostream>
using namespace std;

typedef pair<int, int> ii;
#define MAX_N 55
#define MAX_T 1005
#define INF 2000000000

int i, j, n, t, toll[MAX_N][MAX_N], travelTime[MAX_N][MAX_N];
ii memo[MAX_N][MAX_T];

ii go(int cur, int t_left) { // top-down DP, returns a pair
  if (t_left < 0) return ii(INF, INF); // invalid state
  if (cur == n - 1) return ii(0, 0); // at last city, no need to pay toll and time needed is 0
  if (memo[cur][t_left] != ii(-1, -1)) return memo[cur][t_left]; // visited before
  ii ans = ii(INF, INF);
  for (int nxt = 0; nxt < n; nxt++) if (cur != nxt) { // try to go to another city
    ii nextCity = go(nxt, t_left - travelTime[cur][nxt]); // recursive step
    if (nextCity.first + toll[cur][nxt] < ans.first) { // pick the one that has min cost
      ans.first  = nextCity.first  + toll[cur][nxt];
      ans.second = nextCity.second + travelTime[cur][nxt];
  } }
  return memo[cur][t_left] = ans;
} // store the answer to memo table as well as returning the answer to the caller

int main() {
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

  while (scanf("%d %d", &n, &t), (n || t)) {
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        scanf("%d", &travelTime[i][j]);
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        scanf("%d", &toll[i][j]);

    for (i = 0; i <= n; i++)
      for (j = 0; j <= t; j++)
        memo[i][j] = ii(-1, -1);
    ii res = go(0, t);
    printf("%d %d\n", res.first, res.second);
  }

  return 0;
}
