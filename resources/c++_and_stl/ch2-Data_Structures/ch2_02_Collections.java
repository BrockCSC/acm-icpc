import java.util.*;

class ch2_02_Collections {
  public static void main(String[] args) {
    Vector<Integer> v = new Vector<Integer>();

    v.add(10);
    v.add(5);
    v.add(2);
    v.add(7);
    v.add(1);

    System.out.println("Before sorting:");
    System.out.println(v);

    Collections.sort(v);
    // if we want to modify comparison function, use the overloaded method: Collections.sort(List list, Comparator c);

    System.out.println("After sorting:");
    System.out.println(v);

    int pos = Collections.binarySearch(v, 7);
    System.out.println("Trying to search for 7 in v, found at index = " + pos);

    pos = Collections.binarySearch(v, 8);
    System.out.println("Trying to search for 8 in v, found at index = " + pos); // output is -5 (explanation below)

    /*
    binarySearch will returns:

      index of the search key, if it is contained in the list;
      otherwise, (-(insertion point) - 1).
      The insertion point is defined as the point at which the key would be inserted into the list:
      the index of the first element greater than the key,
      or list.size(), if all elements in the list are less than the specified key.
      Note that this guarantees that the return value will be >= 0 if and only if the key is found. 
    */
  }
}
