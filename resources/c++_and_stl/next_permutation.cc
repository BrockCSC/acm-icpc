/* C++: Next/Prev Permutation with STL
   =================================================================
   Description: This routine shows how to use next/prev permutation
                with STL
   
   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Oct 27, 2002
   References:  http://www.sgi.com/tech/stl/next_permutation.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Any base type can be used, e.g. chars, strings
               -next_permutation returns 1 as long as a next
	        permutation exists.  It modifies the array/vector
		that it is fed to contain the next permutation
		
                
*/

#include <stdio.h>
#include <vector>
#include <algorithm>

typedef struct{
  int x, y;
} Point;

int cmp_strict_less_Point(Point a, Point b){
  if(a.x < b.x) return 1;
  if(a.x == b.x && a.y < b.y) return 1;
  return 0;
}

int main(){
  char buff[100];
  int len;
  unsigned int i;

  /*----------------------------------------*/
  /* For an array                           */
  /*----------------------------------------*/
  scanf(" %s", buff);
  len = strlen(buff);
  while(next_permutation(buff, buff+len)){
    printf("%s\n", buff);
  }
  
  
  /*----------------------------------------*/
  /* For a vector                           */
  /*----------------------------------------*/

  /* For a vector */
  vector<int> vec;
  for(i = 0; i < 3; i++) vec.push_back(3-i);

  while(prev_permutation(vec.begin(), vec.end())){
    for(i = 0; i < vec.size(); i++) printf("%d ", vec[i]);
    printf("\n");
  }
  printf("\n");

  /*----------------------------------------*/
  /* For an array of structs 
     The comparision function must be written 
     - a strictly less than function:
          1 if a < b
          0 otherwise
  /*----------------------------------------*/
  Point p[5];
  for(i = 0; i < 5; i++){
    p[i].x = (3*i)%4;
    p[i].y = (2*i)%7;
  }
  while(next_permutation(p, p+5, cmp_strict_less_Point)){
    for(i = 0; i < 5; i++){
      printf("[%d,%d] ", p[i].x, p[i].y);
    }
    printf("\n");
  }
  return 0;
}
