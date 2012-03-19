/* UVa 11450 - Wedding Shopping - Bottom Up */
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
  int i, j, l, TC, M, C, K, price[25][25]; // price[g (<= 20)][model (<= 20)]
  bool can_reach[210][25]; // can_reach table[money (<= 200)][g (<= 20)]

  scanf("%d", &TC);
  while (TC--) {
    scanf("%d %d", &M, &C);
    for (i = 0; i < C; i++) {
      scanf("%d", &K);
      price[i][0] = K; // to simplify coding, we store K in price[i][0]
      for (j = 1; j <= K; j++)
        scanf("%d", &price[i][j]);
    }

    memset(can_reach, false, sizeof can_reach); // clear everything
    for (i = 1; i <= price[0][0]; i++) // initial values
      if (M - price[0][i] >= 0) // bug fix: to prevent array index out of bound
        can_reach[M - price[0][i]][0] = true; // if only using first garment g = 0

    for (j = 1; j < C; j++) // for each remaining garment (note: this is written in column major)
      for (i = 0; i < M; i++) if (can_reach[i][j - 1]) // if can reach this state
        for (l = 1; l <= price[j][0]; l++) if (i - price[j][l] >= 0) // flag the rest
          can_reach[i - price[j][l]][j] = true; // as long as it is feasible

    for (i = 0; i <= M && !can_reach[i][C - 1]; i++); // the answer is in the last column

    if (i == M + 1) printf("no solution\n"); // nothing in this last column has its bit turned on
    else            printf("%d\n", M - i);
} } // return 0;



///* UVa 11450 - Wedding Shopping - Bottom Up - Row Major - Space Saving Trick */
//#include <cstdio>
//#include <cstring>
//using namespace std;
//
//int main() {
//  int i, j, l, TC, M, C, K, cur, price[25][25]; // price[g (<= 20)][model (<= 20)]
//  bool can_reach[2][210]; // can_reach table[2][money (<= 200)]
//
//  scanf("%d", &TC);
//  while (TC--) {
//    scanf("%d %d", &M, &C);
//    for (i = 0; i < C; i++) {
//      scanf("%d", &K);
//      price[i][0] = K; // to simplify coding, we store K in price[i][0]
//      for (j = 1; j <= K; j++)
//        scanf("%d", &price[i][j]);
//    }
//
//    memset(can_reach, false, sizeof can_reach); // clear everything
//    cur = 1; // set row 1 to be the active row; row !cur (or row 0) becomes the previous row
//    for (i = 1; i <= price[0][0]; i++) // initial values
//      can_reach[!cur][M - price[0][i]] = true; // if only using first garment g = 0
//
//    for (j = 1; j < C; j++) { // for each remaining garment
//      memset(can_reach[cur], false, sizeof can_reach[cur]); // reset this row
//      for (i = 0; i < M; i++) if (can_reach[!cur][i]) // if can reach this state
//        for (l = 1; l <= price[j][0]; l++) if (i - price[j][l] >= 0) // flag the rest
//          can_reach[cur][i - price[j][l]] = true; // as long as it is feasible
//      cur = !cur; // swap active row
//    }
//
//    for (i = 0; i <= M && !can_reach[!cur][i]; i++); // the answer is in the last row
//
//    if (i == M + 1) printf("no solution\n"); // nothing in this last column has its bit turned on
//    else            printf("%d\n", M - i);
// } } // return 0;