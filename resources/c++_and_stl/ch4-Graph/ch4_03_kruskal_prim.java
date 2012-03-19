import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Vector;

public class ch4_03_kruskal_prim {
  // Union-Find Disjoint Sets data structure from chapter 2.
  private static Vector<Integer> pset;
  private static void initSet(int _size) { pset = new Vector<Integer>(_size); for (int i = 0; i < _size; i++) pset.add(i); }
  private static int findSet(int i) { return (pset.get(i) == i) ? i : (pset.set(i, findSet(pset.get(i)))); }
  private static void unionSet(int i, int j) { pset.set(findSet(i), findSet(j)); }
  private static boolean isSameSet(int i, int j) {
	int a = findSet(i);
	int b = findSet(j);
	a = findSet(i); // to avoid bug in Java version, we have to call findSet twice
	b = findSet(j);
    return a == b; 
  }

  public static void main(String[] args) {
    int V, E, a, b, weight;

    /*
    // Graph in Figure 4.9 left/4.10, format: list of weighted edges
    // This example shows another form of reading graph input
    5 7
    1 2 5
    1 3 5
    1 4 5
    1 5 5
    2 3 2
    3 4 8
    4 5 8
    */

    Scanner sc = new Scanner(System.in);
    V = sc.nextInt();
    E = sc.nextInt();

    // another graph data structure: EdgeList
    PriorityQueue < pair < Integer, IntegerPair > > EdgeList = new 
    PriorityQueue < pair < Integer, IntegerPair > >(1, 
      new Comparator< pair < Integer, IntegerPair > >() { // overriding the compare method 
	    public int compare(pair < Integer, IntegerPair > i, pair < Integer, IntegerPair > j) {
	      return j.first() - i.first();
	    }
	  }
	);
          
    // sort by edge weight O(E log E)
    // PQ default: sort descending. Trick: use <(negative) weight(i, j), <i, j> >
    for (int i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      weight = sc.nextInt();
      IntegerPair edge = new IntegerPair (--a, --b);
      EdgeList.offer(new pair < Integer, IntegerPair > (-weight, edge));
    }

    int mst_cost = 0; initSet(V); // all V are disjoint sets at the beginning
    while (!EdgeList.isEmpty()) { // while there exist more edges, O(E)
      pair < Integer, IntegerPair > front = EdgeList.poll();
      a = front.second().first();
      b = front.second().second();
      if (!isSameSet(a, b)) { // if no cycle
        mst_cost += (-front.first()); // add (negated) -weight of e to MST
        unionSet(a, b); // link these two vertices
      }
    }
    System.out.printf("MST cost %d\n", mst_cost);



    // Prim's algorithm is not yet implemented...
  }
}
