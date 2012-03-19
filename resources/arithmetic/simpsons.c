/* Arithmatic: Simpson's Rule for Numerical Intergration
   =================================================================
   Description: Numerical integration of the function f from a to b
                Splits the interval [a,b] into 2k pieces.
		The error is <= (b-a)/180.0 * M * h^4
		where:
		  M = max( abs(f''''(x))) for x in [a,b]
		  h = (b-a)/2k
		Note that this means the integrals for low degree
		polynomials are computed exactly
   
   Complexity:  O(k)
   -----------------------------------------------------------------
   Author:      Adam Beacham, Brian Lau
   Date:        Oct 4, 2002
   References:  Any Calculus book.
   -----------------------------------------------------------------
   Reliability: 0/0
   Notes:        
*/

#include <assert.h>
#include <stdio.h>


double Simpson(double a, double b, int k, double (*f)(double)){
  double dx, x, t;
  int i;
  
  /* assert( (a - b) != 0 && k > 0); */

  dx = (b-a)/(2.0*k);
  t = 0;
  
  for( i=0; i<k; i++ ) {
    t += (i==0 ? 1.0 : 2.0) * (*f)(a+2.0*i*dx);
    t += 4.0 * (*f)(a+(2.0*i+1.0)*dx);
  }
  t += (*f)(b);
  
  return t * (b-a)/6.0/k;
}

double example_function(double x)
{
  return x*x;
}

int main(void)
{
  int k;
  double a = 0, b=5.0;
  
  printf("Integral from %f to %f is:\n",a,b);
  for( k=1; k<=40; k++ ) {
    printf("  k = %3d:  %f\n",k,Simpson(a,b,k,example_function));
  }
  
  return 0;
}
