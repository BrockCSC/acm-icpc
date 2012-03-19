/* 8 Queens Chess Problem */
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

int row[9], TC, a, b, lineCounter; // it is ok to use global variables in competitive programming

bool place(int col, int tryrow) {
  for (int prev = 1; prev < col; prev++) // check previously placed queens
    if (row[prev] == tryrow || (abs(row[prev] - tryrow) == abs(prev - col)))
      return false; // an infeasible solution if share same row or same diagonal
  return true;
}

void backtrack(int col) {
  for (int tryrow = 1; tryrow <= 8; tryrow++) // try all possible row
    if (place(col, tryrow)) { // if can place a queen at this col and row...
      row[col] = tryrow; // put this queen in this col and row
      if (col == 8 && row[b] == a) { // a candidate solution & (a, b) has 1 queen
        printf("%2d      %d", ++lineCounter, row[1]);
        for (int j = 2; j <= 8; j++) printf(" %d", row[j]);
        printf("\n");
      }
      else
        backtrack(col + 1); // recursively try next column
}   }

int main() {
  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &a, &b);
    memset(row, 0, sizeof row); lineCounter = 0;
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n\n");
    backtrack(1); // generate all possible 8! candidate solutions
    if (TC) printf("\n");
  }
  return 0;
}
