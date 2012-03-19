/* Arithmetic: Fast Exponentition
   =================================================================
   Description: Given integer x and nonnegative number N, computes
                x^N quickly
   
   Complexity:  O(lg N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 17, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       x can be negative.  
                N >= 0 otherwise routine will infinitely loop
                The limit for the results is: 
 		  [-9223372036854775808 = -2^63, to 
		   +9223372036854775807 = +2^63 - 1]
*/

#include <stdio.h>

#define LL long long

LL fast_exp(int b, int n){
  LL res = 1, x = b, p;
  
  for(p = n; p; p >>= 1, x *= x)
    if(p & 1) res *= x;
  
  return res;
}

int main(){
  int b, n;

  while(scanf("%d %d", &b, &n) == 2){
    printf("%d^%d = %Ld\n", b, n, fast_exp(b,n));
  }
  return 0;
}
