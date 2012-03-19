/*
 * Fast Exponentiation mod m
 *
 * Author: Howard Cheng
 *
 * Given b, n, and m, computes b^n mod m quickly.
 *
 */

#include <stdio.h>
#include <assert.h>

int fast_exp(int b, int n, int m)
{
  int res = 1;
  int x = b;

  while (n > 0) {
    if (n & 0x01) {
      n--;
      res = (res * x) % m;
    } else {
      n >>= 1;
      x = (x * x) % m;
    }
  }

  return res;
}

int main(void)
{
  int b, n, m;

  while (scanf("%d %d %d", &b, &n, &m) == 3) {
    printf("%d^%d mod %d = %d\n", b, n, m, fast_exp(b, n, m));
  }
  return 0;

}
