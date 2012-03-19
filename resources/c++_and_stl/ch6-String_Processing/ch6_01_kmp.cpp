#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 100010

char T[MAX_N], P[MAX_N]; // T = text, P = pattern
int b[MAX_N], n, m; // b = back table, n = length of T, m = length of P

void naiveMatching() {
  for (int i = 0; i < n; i++) { // try all potential starting indices
    bool found = true;
    for (int j = 0; j < m && found; j++) // use boolean flag `found'
      if (P[j] != T[i + j]) // if mismatch found
        found = false; // abort this, shift starting index i by +1
    if (found) // if P[0 .. m - 1] == T[i .. i + m - 1]
      printf("P is found at index %d in T\n", i);
} }

void kmpPreprocess() { // call this before calling kmpSearch()
  int i = 0, j = -1; b[0] = -1; // starting values
  while (i < m) { // pre-process the pattern string P
    while (j >= 0 && P[i] != P[j]) j = b[j]; // if different, reset j using b
    i++; j++; // if same, advance both pointers
    b[i] = j; // observe i = 8, 9, 10, 11, 12 with j = 0, 1, 2, 3, 4
} }           // in the example of P = "SEVENTY SEVEN" above

void kmpSearch() { // this is similar as kmpPreprocess(), but on string T
  int i = 0, j = 0; // starting values
  while (i < n) { // search through string T
    while (j >= 0 && T[i] != P[j]) j = b[j]; // if different, reset j using b
    i++; j++; // if same, advance both pointers
    if (j == m) { // a match found when j == m
      printf("P is found at index %d in T\n", i - j);
      j = b[j]; // prepare j for the next possible match
} } }

int main() {
  n = (int)strlen(gets(T));
  m = (int)strlen(gets(P));

  printf("Naive\n");
  naiveMatching();

  printf("KMP\n");
  kmpPreprocess();
  kmpSearch();

  return 0;
}
