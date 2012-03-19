import java.util.*;

class ch2_08_unionfind_ds {
  private static Vector<Integer> pset;
  private static void initSet(int _size) { 
    pset = new Vector<Integer>(_size); for (int i = 0; i < _size; i++) pset.add(i); }
  private static int findSet(int i) { 
    if (pset.get(i) == i) return i;
    else {
      int ret = findSet(pset.get(i)); pset.set(i, ret);
      return ret; }
  private static void unionSet(int i, int j) { pset.set(findSet(i), findSet(j)); }
  private static boolean isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  public static void main(String[] args) {
    System.out.println("Assume that there are 5 disjoint sets initially");
    initSet(5); // create 5 disjoint sets
    unionSet('A' - 'A', 'B' - 'A'); // unionSet(A, B)
    unionSet('A' - 'A', 'C' - 'A'); // unionSet(A, C)
    unionSet('D' - 'A', 'B' - 'A'); // unionSet(D, B)
    System.out.println("findSet(A) = " + findSet('A' - 'A')); // will return 1 (lazy update)
    System.out.println("findSet(A) = " + findSet('A' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
    System.out.println("findSet(B) = " + findSet('B' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
    System.out.println("findSet(C) = " + findSet('C' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
    System.out.println("findSet(D) = " + findSet('D' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
    System.out.println("findSet(E) = " + findSet('E' - 'A')); // will return 4 (the parent ID of 'E')
    System.out.println("isSameSet(A, E) = " + isSameSet('A' - 'A', 'E' - 'A')); // will return false
    System.out.println("isSameSet(A, B) = " + isSameSet('A' - 'A', 'B' - 'A')); // will return true
  }
}
