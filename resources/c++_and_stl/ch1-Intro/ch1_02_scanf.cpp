#include <cstdio>
using namespace std;

int N;              // using global variables in contests can be a good strategy
char x[110];    // make it a habit to set array size slightly larger than needed

int main() {
  freopen("ch1_02_scanf_input.txt", "r", stdin);

  scanf("%d\n", &N);
  while (N--) {                        // we simply loop from N, N-1, N-2, ... 0
    scanf("0.%[0-9]...\n", &x);          // if you are surprised with this line,
                                  // check scanf details in www.cppreference.com
    printf("the digits are 0.%s\n", x);
  }
  return 0;
}
