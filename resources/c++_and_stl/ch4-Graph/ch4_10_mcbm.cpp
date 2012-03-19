#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

vector<vii> AdjList;
vi owner, visited; // global variables

int Aug(int left) {
  if (visited[left]) return 0;
  visited[left] = true;
  for (int j = 0; j < (int)AdjList[left].size(); j++) {
    int right = AdjList[left][j].first;
    // either greedy assignment or recurse
    if (owner[right] == -1 || Aug(owner[right])) {
      owner[right] = left;
      return 1; // we found one matching
    }
  }
  return 0; // no matching
}

bool isprime(int v) {
  int primes[10] = {2,3,5,7,11,13,17,19,23,29};
  for (int i = 0; i < 10; i++)
    if (primes[i] == v)
      return true;
  return false;
}

int main() {
  int i, j;

/*
  // Graph in Figure 4.34 can be built on the fly
  // we know there are 6 vertices in this bipartite graph, left side are numbered 0,1,2, right side 3,4,5
  //int V = 6, num_vertices_on_left = 3, set1[3] = {1,7,11}, set2[3] = {4,10,12};

  // Graph in Figure 4.35 can be built on the fly
  // we know there are 5 vertices in this bipartite graph, left side are numbered 0,1, right side 3,4,5
  int V = 5, num_vertices_on_left = 2, set1[2] = {1,7}, set2[3] = {4,10,12};

  // build the bipartite graph, only directed edge from left to right is needed
  AdjList.assign(V, vii());
  for (i = 0; i < num_vertices_on_left; i++)
    for (j = 0; j < 3; j++)
      if (isprime(set1[i] + set2[j]))
        AdjList[i].push_back(ii(3 + j, 0));
*/


  // Graph in Figure 4.37, manual construction
  int V = 4, num_vertices_on_left = 2;
  AdjList.assign(V, vii());
  AdjList[0].push_back(ii(2, 1));
  AdjList[0].push_back(ii(3, 1));
  AdjList[1].push_back(ii(2, 1));


  // the MCBM routine
  int cardinality = 0;
  owner.assign(V, -1);
  for (int left = 0; left < num_vertices_on_left; left++) {
    visited.assign(num_vertices_on_left, 0);
    cardinality += Aug(left);
  }

  printf("Found %d matchings\n", cardinality);

  return 0;
}