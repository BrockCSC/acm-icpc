import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;

public class ch4_06_bellman_ford {
  public static final int INF = 2000000000;
  private static Vector< Vector< IntegerPair > > AdjList =
             new Vector< Vector< IntegerPair > >();
	  
  public static void main(String[] args) {
    int V, E, a, b, weight;

    /*
    // Graph in Figure 4.17, no negative cycle
    5 5
    0 1 1
    0 2 10
    1 3 2
    2 3 -10
    3 4 3

    // Graph in Figure 4.18, negative cycle exists
    3 3
    0 1 1000
    1 2 15
    2 1 -42
    */

    Scanner sc = new Scanner(System.in);
    V = sc.nextInt();
    E = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++) {
      Vector< IntegerPair > Neighbor = 
        new Vector < IntegerPair >();
      AdjList.add(Neighbor); // add neighbor list to Adjacency List
    }

    for (int i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      weight = sc.nextInt();
      AdjList.get(a).add(new IntegerPair(b, weight)); // first time using weight
    }
    
    // as an example, we start from this source (see Figure 1.15)
    int s = 0;
    Vector< Integer > dist = new Vector< Integer >();
    dist.addAll(Collections.nCopies(V, INF));
    dist.set(s, 0);

    // Bellman Ford routine
    for (int i = 0; i < V - 1; i++) // relax all E edges V-1 times, O(V)
      for (int u = 0; u < V; u++) { // these two loops = O(E)
        Iterator it = AdjList.get(u).iterator();
        while (it.hasNext()) { // relax these edges
          IntegerPair v = (IntegerPair)it.next();
          dist.set(v.first(), 
            Math.min(dist.get(v.first()), dist.get(u) + v.second()));
        }
      }

    boolean negative_cycle_exist = false;
    for (int u = 0; u < V; u++) { // one more pass to check
      Iterator it = AdjList.get(u).iterator();
      while (it.hasNext()) { // relax these edges
        IntegerPair v = (IntegerPair)it.next();
        if (dist.get(v.first()) > dist.get(u) + v.second()) // should be false, but if possible
          negative_cycle_exist = true;            // then negative cycle exists!
      }
    }

    System.out.printf("Negative Cycle Exist? %s\n", negative_cycle_exist ? "Yes" : "No");

    if (!negative_cycle_exist)
      for (int i = 0; i < V; i++)
        System.out.printf("SSSP(%d, %d) = %d\n", s, i, dist.get(i));
  }
}
