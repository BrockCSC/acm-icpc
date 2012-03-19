import java.util.*;

class ch6_03_sa {
  Scanner scan;
  char T[];                        // the input string, up to 100K characters
  int n;                                             // the length of input string

  int[] RA, tempRA;             // rank array and temporary rank array
  Integer[] SA, tempSA;         // suffix array and temporary suffix array
  int[] c;                                         // for counting/radix sort

  char P[];     // the pattern string (for string matching)
  int m;             // the length of pattern string

  int[] Phi;    // for computing longest common prefix
  int[] PLCP;
  int[] LCP;    // LCP[i] stores the LCP between previous suffix "T + SA[i-1]" and current suffix "T + SA[i]"

  void constructSA_slow() {                    // cannot go beyond 1000 characters
    for (int i = 0; i < n; i++) SA[i] = i;      // initial SA: {0, 1, 2, ..., n-1}

    Arrays.sort(SA, 0, n, new Comparator<Integer>(){
      public int compare(Integer a, Integer b) {
        for (int i=0; a+i < T.length && b+i < T.length; i++){
          if (T[a+i] != T[b+i]) return T[a+i] - T[b+i];
        }
        return b - a; // to break ties
      }
    });   // sort: O(n log n) * comparison: O(n) = O(n^2 log n)
  }

  void countingSort(int k) {
    int i, sum, maxi = Math.max(300, n);   // up to 255 ASCII chars or length of n
    for (i = 0; i < 100010; i++) c[i] = 0;                // clear frequency table
    for (i = 0; i < n; i++)                    // count the frequency of each rank
      c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
      int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; i++)               // shuffle the suffix array if necessary
      tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)                          // update the suffix array SA
      SA[i] = tempSA[i];
  }

  void constructSA() {              // this version can go up to 100000 characters
    int i, k, r;
    for (i = 0; i < n; i++) RA[i] = T[i] - '.';                // initial rankings
    for (i = 0; i < n; i++) SA[i] = i;          // initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1) {            // repeat sorting process log n times
      countingSort(k);       // actually radix sort: sort based on the second item
      countingSort(0);               // then (stable) sort based on the first item
      tempRA[SA[0]] = r = 0;                  // re-ranking; start from rank r = 0
      for (i = 1; i < n; i++)                         // compare adjacent suffices
        tempRA[SA[i]] =      // if same pair => same rank r; otherwise, increase r
          (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
      for (i = 0; i < n; i++)                          // update the rank array RA
        RA[i] = tempRA[i];
  } }

  void computeLCP_slow() {
    LCP[0] = 0;                                                   // default value
    for (int i = 1; i < n; i++) {                     // compute LCP by definition
      int L = 0;                                            // always reset L to 0
      while (T[SA[i] + L] == T[SA[i-1] + L]) L++;   // L-th chars same, increase L
      LCP[i] = L;
  } }

  void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;                                              // default value
    for (i = 1; i < n; i++)                                 // compute Phi in O(n)
      Phi[SA[i]] = SA[i-1];         // remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++) {                  // compute Permuted LCP in O(n)
      if (Phi[i] == -1) { PLCP[i] = 0; continue; }                 // special case
      while (i + L < T.length && Phi[i] + L < T.length && T[i + L] == T[Phi[i] + L]) L++; // L will be increased max n times
      PLCP[i] = L;
      L = Math.max(L-1, 0);                          // L will be decreased max n times
    }
    for (i = 1; i < n; i++)                                 // compute LCP in O(n)
      LCP[i] = PLCP[SA[i]];   // put the permuted LCP back to the correct position
  }

  int strncmp(char[] a, int i, char[] b, int j, int n){
    for (int k=0; i+k < a.length && j+k < b.length; k++){
      if (a[i+k] != b[j+k]) return a[i+k] - b[j+k];
    }
    return 0;
  }

  int[] stringMatching() {                           // string matching in O(m log n)
    int lo = 0, hi = n-1, mid = lo;                 // valid matching = [0 .. n-1]
    while (lo < hi) {                                          // find lower bound
      mid = (lo + hi) / 2;                                   // this is round down
      int res = strncmp(T, SA[mid], P, 0, m);       // try to find P in suffix 'mid'
      if (res >= 0) hi = mid;             // prune upper half (notice the >= sign)
      else          lo = mid + 1;                // prune lower half including mid
    }                                           // observe `=' in "res >= 0" above
    if (strncmp(T,SA[lo], P,0, m) != 0) return new int[]{-1, -1};         // if not found
    int[] ans = new int[]{ lo, 0} ;

    lo = 0; hi = n - 1; mid = lo;
    while (lo < hi) {                 // if lower bound is found, find upper bound
      mid = (lo + hi) / 2;
      int res = strncmp(T, SA[mid], P,0, m);
      if (res > 0) hi = mid;                                   // prune upper half
      else         lo = mid + 1;                 // prune lower half including mid
    }                                // (notice the selected branch when res == 0)
    if (strncmp(T, SA[hi], P,0, m) != 0) hi--;                      // special case
    ans[1] = hi;
    return ans;
  } // return lower/upper bound as the first/second item of the pair, respectively

  void LRS() {                          // print out the length and the actual LRS
    int i, idx = 0, maxLCP = 0;

    for (i = 1; i < n; i++)                                                // O(n)
      if (LCP[i] > maxLCP) {
        maxLCP = LCP[i];
        idx = i;
      }

    System.out.printf("The LRS is '%s' with length = %d\n",
      new String(T).substring(SA[idx], maxLCP), maxLCP);
  }

  int owner(int idx) { return (idx < n-m-1) ? 1 : 2; }

  void LCS() {                          // print out the length and the actual LCS
    int i, j, maxLCP = 0, idx = 0;
    // not used in Java version
    // char ans[MAX_N];
    // strcpy(ans, "");
    
    System.out.printf("\nRemember, T = '%s'\nNow, enter another string P:\n", new String(T));
    // T already has '.' at the back
    P = scan.nextLine().toCharArray();
    m = P.length;
    T = (new String(T) + new String(P) + "/").toCharArray();   // append P and '/'
    n = T.length;                                                      // update n
    constructSA_slow();                                              // O(n log n)
    computeLCP();                                                          // O(n)
    System.out.printf("\nThe LCP information of 'T.P' = '%s':\n", new String(T));
    System.out.printf("i\tSA[i]\tLCP[i]\tOwner\tSuffix\n");
    for (i = 0; i < n; i++)
      System.out.printf("%2d\t%2d\t%2d\t%2d\t%s\n", i, SA[i], LCP[i], owner(SA[i]),
        new String(T, SA[i], T.length - SA[i]));

    for (i = 1, maxLCP = -1; i < n; i++)
      if (LCP[i] > maxLCP && owner(SA[i]) != owner(SA[i-1])) {  // different owner
        maxLCP = LCP[i];
        idx = i;
        // not used in Java version
        // strncpy(ans, T + SA[i], maxLCP);
        // ans[maxLCP] = 0;
      }

    System.out.printf("The LCS is '%s' with length = %d\n",
      new String(T).substring(SA[idx], SA[idx] + maxLCP),
      maxLCP);
  }

  void run() {
    int MAX_N = 100010;
    c = new int[MAX_N];
    RA = new int[MAX_N];
    tempRA = new int[MAX_N];
    SA = new Integer[MAX_N];
    tempSA = new Integer[MAX_N];
    Phi = new int[MAX_N];
    PLCP = new int[MAX_N];
    LCP = new int[MAX_N];

    scan = new Scanner(System.in);

    System.out.printf("Enter a string T below, we will compute its Suffix Array:\n");
    T = scan.nextLine().toCharArray();
    n = T.length;

    constructSA_slow();                                            // O(n^2 log n)
    System.out.printf("\nThe Suffix Array of string T = '%s' is shown below (O(n^2 log n) version):\n", new String(T));
    System.out.printf("i\tSA[i]\tSuffix\n");
    for (int i = 0; i < n; i++)
     System.out.printf("%2d\t%2d\t%s\n", i, SA[i], new String(T, SA[i], T.length - SA[i]));

    T = (new String(T) + ".").toCharArray();                 // important bug fix!
    constructSA();                                                   // O(n log n)
    System.out.printf("\nThe Suffix Array of string T = '%s' is shown below (O(n log n) version):\n", new String(T));
    System.out.printf("i\tSA[i]\tSuffix\n");
    for (int i = 0; i < n; i++)
     System.out.printf("%2d\t%2d\t%s\n", i, SA[i], new String(T, SA[i], T.length - SA[i]));

    computeLCP();                                                          // O(n)
    LRS();        // find the longest repeated substring of the first input string

    System.out.printf("\nNow, enter a string P below, we will try to find P in T:\n");
    System.out.printf("Enter an empty string to stop this string search demo!\n");
    while (true) {  // stop when an empty string is entered
      P = scan.nextLine().toCharArray();
      if ((m = P.length) == 0) break;
      int[] pos = stringMatching();
      if (pos[0] != -1 && pos[1] != -1) {
        System.out.printf("%s is found SA [%d .. %d] of %s\n", 
          new String(P), pos[0], pos[1], new String(T));
        System.out.printf("They are:\n");
        for (int i = pos[0]; i <= pos[1]; i++)
          System.out.printf("  %s\n", new String(T, SA[i], T.length - SA[i]));
      } else System.out.printf("%s is not found in %s\n", new String(P), new String(T));
    }

    LCS();                    // find the longest common substring between T and P
  }

  public static void main(String[] args){
    new ch6_03_sa().run();
  }
}
