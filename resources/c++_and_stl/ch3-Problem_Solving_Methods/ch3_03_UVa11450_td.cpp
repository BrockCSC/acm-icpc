/* UVa 11450 - Wedding Shopping - Top Down */
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int M, C, K, price[25][25]; // price[g (<= 20)][model (<= 20)]
int memo[210][25]; // dp table memo[money (<= 200)][g (<= 20)]

int shop(int money, int g) {
  if (money < 0)            return -1000000000; // fail, return a large negative number (1B)
  if (g == C)               return M - money; // we have bought last garment, done
  if (memo[money][g] != -1) return memo[money][g]; // this state has been visited before
  int ans = -1000000000;
  for (int model = 1; model <= price[g][0]; model++) // try all possible models
    ans = max(ans, shop(money - price[g][model], g + 1));
  return memo[money][g] = ans; // assign ans to dp table + return it!
}

int main() { // easy to code if you are already familiar with it
  int i, j, TC, score;

  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (i = 0; i < C; i++) {
      scanf("%d", &K);
      price[i][0] = K; // to simplify coding, we store K in price[i][0]
      for (j = 1; j <= K; j++)
        scanf("%d", &price[i][j]);
    }

    memset(memo, -1, sizeof memo); // initialize DP memo table
    score = shop(M, 0); // start the top-down DP
    if (score < 0) printf("no solution\n");
    else           printf("%d\n", score);
} } // return 0;