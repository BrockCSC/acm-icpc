/* Modular Fibonacci */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
ll MOD;

#define MAX_N 2                                  // increase this if needed
struct Matrix { ll mat[MAX_N][MAX_N]; };     // to let us return a 2D array

Matrix matMul(Matrix a, Matrix b) {              // O(n^3), but O(1) as n=2
  Matrix ans; int i, j, k;
  for (i = 0; i < MAX_N; i++)
    for (j = 0; j < MAX_N; j++)
      for (ans.mat[i][j] = k = 0; k < MAX_N; k++) {
        ans.mat[i][j] += (a.mat[i][k] % MOD) * (b.mat[k][j] % MOD);
        ans.mat[i][j] %= MOD;             // modulo arithmetic is used here
      }
  return ans;
}

Matrix matPow(Matrix base, int p) {    // O(n^3 log p), but O(log p) as n=2
  Matrix ans; int i, j;
  for (i = 0; i < MAX_N; i++)
    for (j = 0; j < MAX_N; j++)
      ans.mat[i][j] = (i == j);                  // prepare identity matrix
  while (p) {       // iterative version of Divide & Conquer exponentiation
    if (p & 1)                    // check if p is odd (the last bit is on)
      ans = matMul(ans, base);                                // update ans
    base = matMul(base, base);                           // square the base
    p >>= 1;                                               // divide p by 2
  }
  return ans;
}

int normalExp(int base, int p) {    // for simplicity, we use int data type
  int ans = 1;
  for (int i = 0; i < p; i++) ans *= base;                          // O(p)
  return ans; }

int fastExp(int base, int p) {                                  // O(log p)
       if (p == 0) return 1;
  else if (p == 1) return base;
  else {           int res = fastExp(base, p / 2); res *= res;
                   if (p % 2 == 1) res *= base;
                   return res; } }

int main() {
  // just for illustration (not part of UVa 10229 solution), uncomment to compare
  // printf("%d vs %d\n", normalExp(2, 4), fastExp(2, 4));
  // printf("%d vs %d\n", normalExp(2, 9), fastExp(2, 9));
  // printf("%d vs %d\n", normalExp(2, 22), fastExp(2, 22));

  int i, n, m;

  while (scanf("%d %d", &n, &m) == 2) {
    Matrix ans;                                // special Fibonaccci matrix
    ans.mat[0][0] = 1;  ans.mat[0][1] = 1;
    ans.mat[1][0] = 1;  ans.mat[1][1] = 0;
    for (MOD = 1, i = 0; i < m; i++)                       // set MOD = 2^m
      MOD *= 2;
    ans = matPow(ans, n);                                       // O(log n) 
    printf("%lld\n", ans.mat[0][1]);                      // this if fib(n)
  }

  return 0;
}
