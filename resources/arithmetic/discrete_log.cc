/* Arithmetic: Discrete Logarithm solver
   =================================================================
   Description: Given prime P, B, and N, finds the smallest 
                exponent L such that B^L == N (mod P)
   
   Complexity:  O(sqrt(P))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 13, 2002
   References:  http://plg.uwaterloo.ca/~acm00/020126/data/B.cpp
   -----------------------------------------------------------------
   Reliability: 1 successful use (Spain Problem 10225) Sept 2002
   Notes:       The function either returns the exponent L, or
                -1 if no solution is found
*/

#include <stdio.h>
#include <map>
#include <math.h>

using namespace std;

#define UI unsigned
#define UL unsigned long
#define ULL unsigned long long

map<UI,UI> M;

UL times (UL a, UL b, UL m){
  return (ULL) a * b % m;
}

UL power(UL val, UL power, UL m){
  UL res = 1, p;
  
  for(p = power; p; p=p>>1){
    if(p & 1) res = times(res, val, m);
    val = times(val, val, m);
  }
  return res;
}

int discrete_log(UI p, UI b, UI n){
  UL i, j, jump;
  
  M.clear();
  jump = (int)sqrt(p);
  for (i = 0; i < jump && i < p-1; i++){
    M[power(b,i,p)] = i+1;
  }
  for (i = 0; i < p-1; i+= jump){
    if (j = M[times(n,power(b,p-1-i,p),p)]) {
      j--;
      return (i+j)%(p-1);
    }
  }
  return -1;
}

int main(){
  UI p, b, n;
  int x;

  while(scanf("%d %d %d", &p, &b, &n) == 3){
    x = discrete_log(p,b,n);
    if(x < 0) printf("no solution\n");
    else printf("%d\n", x);
  }
  return 0;
}
