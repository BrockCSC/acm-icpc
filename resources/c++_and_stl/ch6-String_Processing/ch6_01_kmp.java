import java.util.*;

class ch6_01_kmp {
  char[] T, P; // T = text, P = pattern
  int n, m; // n = length of T, m = length of P
  int [] b; // b = back table

  void naiveMatching() {
    for (int i = 0; i < n; i++) { // try all potential starting indices
      boolean found = true;
      for (int j = 0; j < m && found; j++) // use boolean flag `found'
        if (P[j] != T[i + j]) // if mismatch found
          found = false; // abort this, shift starting index i by +1
      if (found) // if P[0 .. m - 1] == T[i .. i + m - 1]
        System.out.printf("P is found at index %d in T\n", i);
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
        System.out.printf("P is found at index %d in T\n", i - j);
        j = b[j]; // prepare j for the next possible match
  } } }

  void run() {
    Scanner scan = new Scanner(System.in);
    T = scan.nextLine().toCharArray();
    P = scan.nextLine().toCharArray();
    n = T.length;
    m = P.length;
    b = new int[100010];

    System.out.printf("Naive\n");
    naiveMatching();

    System.out.printf("KMP\n");
    kmpPreprocess();
    kmpSearch();
  }

  public static void main(String[] args){
    new ch6_01_kmp().run();
  }
}
