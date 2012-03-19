import java.util.*;

class ch2_04_bit_manipulation {
  private static int setBit(int S, int j) { return S | (1 << j); }

  private static int isOn(int S, int j) { return S & (1 << j); }

  private static int clearBit(int S, int j) { return S & ~(1 << j); }

  private static int toggleBit(int S, int j) { return S ^ (1 << j); }

  private static int lowBit(int S) { return S & (-S); }

  private static int setAll(int n) { return (1 << n) - 1; }

  private static int modulo(int x, int N) { return ((x) & (N - 1)); } // returns x % N, where N is a power of 2

  private static int isPowerOfTwo(int x) { return (x & (x - 1)); }

  private static int nearestPowerOfTwo(int x) { return ((int)Math.pow(2.0, (int)((Math.log((double)x) / Math.log(2.0)) + 0.5))); }

  private static void printSet(int _S) {             // in binary representation
    System.out.printf("S = %2d = ", _S);
    Stack<Integer> st = new Stack<Integer>();
    while (_S > 0) {
      st.push(_S % 2);
      _S /= 2;
    }
    while (!st.empty()) {                          // to reverse the print order
      System.out.printf("%d", st.peek());
      st.pop();
    }
    System.out.printf("\n");
  }

  public static void main(String[] args) {
    int S, T;

    System.out.printf("1. Representation (all indexing are 0-based and counted from right)\n");
    S = 34; printSet(S);
    System.out.printf("\n");

    System.out.printf("2. Multiply S by 2, then divide S by 4 (2x2), then by 2\n");
    S = 34; printSet(S);
    S = S << 1; printSet(S);
    S = S >> 2; printSet(S);
    S = S >> 1; printSet(S);
    System.out.printf("\n");

    System.out.printf("3. Set/turn on the 3-th item of the set\n");
    S = 34; printSet(S);
    S = setBit(S, 3); printSet(S);
    System.out.printf("\n");

    System.out.printf("4. Check if the 3-th and then 2-nd item of the set is on?\n");
    S = 42; printSet(S);
    T = isOn(S, 3); System.out.printf("T = %d, %s\n", T, T != 0 ? "ON" : "OFF");
    T = isOn(S, 2); System.out.printf("T = %d, %s\n", T, T != 0 ? "ON" : "OFF");
    System.out.printf("\n");

    System.out.printf("5. Clear/turn off the 1-st item of the set\n");
    S = 42; printSet(S);
    S = clearBit(S, 1); printSet(S);
    System.out.printf("\n");

    System.out.printf("6. Toggle the 2-nd item and then 3-rd item of the set\n");
    S = 40; printSet(S);
    S = toggleBit(S, 2); printSet(S);
    S = toggleBit(S, 3); printSet(S);
    System.out.printf("\n");

    System.out.printf("7. Check the first bit from right that is on\n");
    S = 40; printSet(S);
    T = lowBit(S); System.out.printf("T = %d (this is always a power of 2)\n", T);
    S = 52; printSet(S);
    T = lowBit(S); System.out.printf("T = %d (this is always a power of 2)\n", T);
    System.out.printf("\n");

    System.out.printf("8. Turn on all bits in a set of size n = 6\n");
    S = setAll(6); printSet(S);
    System.out.printf("\n");

    System.out.printf("9. Other tricks (not shown in the book)\n");
    System.out.printf("8 %c 4 = %d\n", '%', modulo(8, 4));
    System.out.printf("7 %c 4 = %d\n", '%', modulo(7, 4));
    System.out.printf("6 %c 4 = %d\n", '%', modulo(6, 4));
    System.out.printf("5 %c 4 = %d\n", '%', modulo(5, 4));
    System.out.printf("is %d power of two? %d\n", 9, isPowerOfTwo(9));
    System.out.printf("is %d power of two? %d\n", 8, isPowerOfTwo(8));
    System.out.printf("is %d power of two? %d\n", 7, isPowerOfTwo(7));
    for (int i = 0; i <= 16; i++)
      System.out.printf("Nearest power of two of %d is %d\n", i, nearestPowerOfTwo(i));
    System.out.printf("\n");
  }
}
