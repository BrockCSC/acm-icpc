/* Miscellaneous: Coupons Problem
   =================================================================
   Description: Coupons are given away in boxes of cereal.  There are 
		'm' different kinds of coupons (with equiprobable 
		distribution).  How many boxes of cereal would you 
		have to buy, on average, to collect them all?

   Complexity:	O(N)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 19, 2003
   References:  http://mathforum.org/library/drmath/view/56657.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ncoupons(int m) {
  double num = 0.0;
  int i;

  for (i = 1; i <= m; i++) num += m/(double) i;
  return num;
}

/* A related problem:  If you buy 'n' boxes of cereal, what is the
   probability you get at least one of each of the 'm' coupons?  
   This is solved by the T(n,m) function.  The T(n,m) function is 
   recursive, so this implementation creates a table using dynamic
   programming (only once) and queries it thereafter.  Like most 
   combinatoric problems, this one blows up very fast.  This solution 
   works for n < 100. */

double nways[100][100];

void make_coupon_table() {
  double fact = 1.0;
  int i, j;

  for (i = 1; i < 100; i++) {
    nways[i][1] = 1.0;
    for (j = 2; j < i; j++)
      nways[i][j] = j*(nways[i-1][j] + nways[i-1][j-1]);
    nways[i][i] = fact *= i;
  }
}

double query_table(int m, int n) {
  if (n < m) return 0.0;
  if (m == 0) return 1.0;
  if (n >= 100 || m >= 100) exit(1);
  return nways[n][m]/pow(m,n);
}

int main() {
  int i, j;

  for (i = 1; i < 34; i++)
    printf("On average, it takes %g boxes to collect all %d\n", 
           ncoupons(i), i);
  make_coupon_table();
  for (i = 0; i < 100; i++) {
    printf("With %d boxes, there is a ",i);
    printf("%g probability of collecting all 26\n", 
           query_table(26,i));
  }
  return 0;
}
