import java.util.*;
import java.text.*;

class ch4_10_mcbm {
  private static Vector < Vector < IntegerPair > > AdjList = 
    new Vector < Vector < IntegerPair > >();
  private static Vector < Integer > owner, visited; // global variables

  private static int Aug(int left) {
    if (visited.get(left) == 1) return 0;
    visited.set(left, 1);

    Iterator it = AdjList.get(left).iterator();
    while (it.hasNext()) { // either greedy assignment or recurse
      IntegerPair right = (IntegerPair)it.next();
      if (owner.get(right.first()) == -1 || Aug(owner.get(right.first())) == 1) {
        owner.set(right.first(), left);
        return 1; // we found one matching
      }
    }

    return 0; // no matching
  }

  private static Boolean isprime(int v) {
    int primes[] = new int[] {2,3,5,7,11,13,17,19,23,29};
    for (int i = 0; i < 10; i++)
      if (primes[i] == v)
        return true;
    return false;
  }

  public static void main(String[] args) {
    int i, j;

/*
    // Graph in Figure 4.34 can be built on the fly
    // we know there are 6 vertices in this bipartite graph, left side are numbered 0,1,2, right side 3,4,5
    //int V = 6, num_vertices_on_left = 3;
    //int set1[] = new int[] {1,7,11}, set2[] = new int[] {4,10,12};

    // Graph in Figure 4.35 can be built on the fly
    // we know there are 5 vertices in this bipartite graph, left side are numbered 0,1, right side 3,4,5
    int V = 5, num_vertices_on_left = 2;
    int set1[] = new int[] {1,7}, set2[] = new int[] {4,10,12};

    // build the bipartite graph, only directed edge from left to right is needed
    AdjList.clear();
    for (i = 0; i < V; i++) {
      Vector<IntegerPair> Neighbor = new Vector<IntegerPair>();
      AdjList.add(Neighbor); // store blank vector first
    }
    
    for (i = 0; i < num_vertices_on_left; i++)
      for (j = 0; j < 3; j++)
        if (isprime(set1[i] + set2[j]))
          AdjList.get(i).add(new IntegerPair(3 + j, 0));

*/

    // Graph in Figure 4.37, manual construction
    int V = 4, num_vertices_on_left = 2;
    AdjList.clear();
    for (i = 0; i < V; i++) {
      Vector<IntegerPair> Neighbor = new Vector<IntegerPair>();
      AdjList.add(Neighbor); // store blank vector first
    }
    AdjList.get(0).add(new IntegerPair(2, 1));
    AdjList.get(0).add(new IntegerPair(3, 1));
    AdjList.get(1).add(new IntegerPair(2, 1));

    // the MCBM routine
    int cardinality = 0;
    owner = new Vector < Integer > ();
    owner.addAll(Collections.nCopies(V, -1));
    for (int left = 0; left < num_vertices_on_left; left++) {
      visited = new Vector < Integer > ();
      visited.addAll(Collections.nCopies(num_vertices_on_left, 0));
      cardinality += Aug(left);
    }

    System.out.printf("Found %d matchings\n", cardinality);
  }
}
