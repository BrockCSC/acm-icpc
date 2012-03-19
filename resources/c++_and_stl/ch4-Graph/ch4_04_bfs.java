import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.Vector;

public class ch4_04_bfs {
  private static int V, E, s;
  private static Vector< Vector< IntegerPair > > AdjList =
             new Vector< Vector< IntegerPair > >();
  private static Map < Integer, Integer > mapper = new TreeMap < Integer, Integer > ();
  private static Map < Integer, Integer > reverseMapper = new TreeMap < Integer, Integer > ();
  private static Vector < Integer > p = new Vector < Integer > ();

  private static void printpath(int u) {
    if (u == s) { System.out.printf("%d", reverseMapper.get(u)); return; }
    printpath(p.get(u));
    System.out.printf(" %d", reverseMapper.get(u));
  }
  
  public static void main(String[] args) {
    int a, b, counter;

    /*
    // Graph in Figure 4.8, format: list of unweighted edges
    // This example shows another form of reading graph input
    13 16
    10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65
    15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65
    */

    Scanner sc = new Scanner(System.in);
    V = sc.nextInt();
    E = sc.nextInt();

    AdjList.clear();
    for (int i = 0; i < V; i++) {
      Vector< IntegerPair > Neighbor = new Vector < IntegerPair >();
      AdjList.add(Neighbor); // add neighbor list to Adjacency List
    }

    counter = 0;
    for (int i = 0; i < E; i++) {
      a = sc.nextInt();
      b = sc.nextInt();
      if (!mapper.containsKey(a)) { // mapping trick
        mapper.put(a, counter++);
        reverseMapper.put(mapper.get(a), a);
      }
      if (!mapper.containsKey(b)) {
        mapper.put(b, counter++);
        reverseMapper.put(mapper.get(b), b);
      }
      AdjList.get(mapper.get(a)).add(new IntegerPair(mapper.get(b), 0));
      AdjList.get(mapper.get(b)).add(new IntegerPair(mapper.get(a), 0));
    }

    // as an example, we start from this source
    // see Figure 4.8
    s = mapper.get(35);

    // BFS routine
    // inside void main(String[] args) -- we do not use recursion, thus we do not need to create separate function!
    int layer = -1; // for our output printing purpose
    p.clear();
    p.addAll(Collections.nCopies(V, 0)); // to store parent information (p must be a global variable!)
    Queue < Integer > q = new LinkedList < Integer > ();
    q.offer(s);
    Map < Integer, Integer > dist = new TreeMap < Integer, Integer > ();
    dist.put(s, 0); // start from source

    while (!q.isEmpty()) {
      int u = q.poll(); // queue: layer by layer!
      if (dist.get(u) != layer) System.out.printf("\nLayer %d:", dist.get(u));
      layer = dist.get(u);
      System.out.printf(", visit %d", reverseMapper.get(u)); // reverseMapper maps index to actual vertex label
      Iterator it = AdjList.get(u).iterator();
      while (it.hasNext()) { // for each neighbours of u
        IntegerPair v = (IntegerPair)it.next();
        if (!dist.containsKey(v.first())) { // if v not visited before
          dist.put(v.first(), dist.get(u) + 1); // then v is reachable from u
          q.offer(v.first()); // enqueue v for next steps
          p.set(v.first(), u); // parent of v is u
        }
      }
    }

    System.out.printf("\nShortest path: ");
    printpath(mapper.get(30));
    System.out.printf("\n");
  }
}