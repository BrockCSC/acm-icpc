import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Vector;

public class ch4_05_dijkstra {
  public static final int INF = 2000000000;
  private static Vector< Vector< IntegerPair > > AdjList = new Vector< Vector< IntegerPair > >();
  
  public static void main(String[] args) {
    int V, E, a, b, weight;

    /*
    // Graph in Figure 4.16
    5 7
    2 1 2
    2 3 7
    2 5 6
    1 3 3
    1 4 6
    3 4 5
    5 4 1
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
      a = sc.nextInt(); a--; // decrease index by 1
      b = sc.nextInt(); b--;
      weight = sc.nextInt();
      AdjList.get(a).add(new IntegerPair (b, weight)); // first time using weight
    }

    // as an example, we start from this source (see Figure 4.16)
    int s = 2 - 1; // index 2 is decreased by 1

    // Dijkstra routine
    Vector < Integer > dist = new Vector < Integer > ();
    dist.addAll(Collections.nCopies(V, INF)); dist.set(s, 0); // INF = 2.10^9 not MAX_INT to avoid overflow
    PriorityQueue < IntegerPair > pq = new PriorityQueue < IntegerPair >(1, 
      new Comparator< IntegerPair >() { // overriding the compare method 
        public int compare(IntegerPair i, IntegerPair j) {
          return i.first() - j.first();
        }
      }
    );
    pq.offer(new IntegerPair (0, s)); // sort based on increasing distance

    while (!pq.isEmpty()) { // main loop
      IntegerPair top = pq.poll(); // greedy: pick shortest unvisited vertex
      int d = top.first(), u = top.second();
      if (d <= dist.get(u)) { // This check is important! We want to process vertex u only once but we can
        // actually enqueue u several times in priority_queue... Fortunately, other occurrences of u
        // in priority_queue will have greater distances and can be ignored (the overhead is small) :)
        Iterator it = AdjList.get(u).iterator();
        while (it.hasNext()) { // all outgoing edges from v
          IntegerPair p = (IntegerPair) it.next();
          int v = p.first(), weight_u_v = p.second();
          if (dist.get(u) + weight_u_v < dist.get(v)) { // if can relax      (note: Record SP spanning tree)
            dist.set(v, dist.get(u) + weight_u_v); // relax                  (here if needed. This is similar)
            pq.offer(new IntegerPair(dist.get(v), v)); //      (as printpath in BFS)
            // enqueue this neighbor regardless whether it is already in pq or not    
    } } } }
  
    for (int i = 0; i < V; i++) // index + 1 for final answer
      System.out.printf("SSSP(%d, %d) = %d\n", s + 1, i + 1, dist.get(i));
  }
}
