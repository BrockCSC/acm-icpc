#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;      // In this chapter, we will frequently use these
typedef vector<ii> vii;      // three data type shortcuts. They may look cryptic
typedef vector<int> vi;   // but shortcuts are useful in competitive programming

int V, E, a, b, counter, s;
vector<vii> AdjList;
map<int, int> mapper, reverseMapper;
  vi p;                               // addition: the predecessor/parent vector

void printPath(int u) {    // simple function to extract information from `vi p'
  if (u == s) { printf("%d", reverseMapper[u]); return; }
  printPath(p[u]);   // recursive call: to make the output format: s -> ... -> t
  printf(" %d", reverseMapper[u]); }

int main() {
  /*
  // Graph in Figure 4.2, format: list of unweighted edges
  // This example shows another form of reading graph input
  13 16
  10 15   15 20   20 25   10 30   30 47   47 50   25 45   45 65
  15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65

  // Subset of Figure 4.2 where the graph is bipartite (remove edge 30-47)
  13 15
  10 15   15 20   20 25   10 30           47 50   25 45   45 65
  15 35   35 55   20 40   50 55   35 40   55 60   40 60   60 65
  */

  scanf("%d %d", &V, &E);

  counter = 0;
  AdjList.assign(V, vii()); // assign blank vectors of pair<int, int>s to AdjList
  for (int i = 0; i < E; i++) {
    scanf("%d %d", &a, &b);
    if (mapper.find(a) == mapper.end()) { // mapping trick
      mapper[a] = counter++;
      reverseMapper[mapper[a]] = a;
    }
    if (mapper.find(b) == mapper.end()) {
      mapper[b] = counter++;
      reverseMapper[mapper[b]] = b;
    }
    AdjList[mapper[a]].push_back(ii(mapper[b], 0));
    AdjList[mapper[b]].push_back(ii(mapper[a], 0));
  }

  // as an example, we start from this source
  // see Figure 4.2
  s = mapper[35];

  // BFS routine
  // inside int main() -- we do not use recursion, thus we do not need to create separate function!
  map<int, int> dist; dist[s] = 0;          // distance to source is 0 (default)
  queue<int> q; q.push(s);                                  // start from source
  p.assign(V, -1); // to store parent information (p must be a global variable!)
  int layer = -1;                             // for our output printing purpose
  bool isBipartite = true;       // addition of one boolean flag, initially true

  while (!q.empty()) {
    int u = q.front(); q.pop();                        // queue: layer by layer!
    if (dist[u] != layer) printf("\nLayer %d:", dist[u]);
    layer = dist[u];
    printf(", visit %d", reverseMapper[u]); // reverseMapper maps index to actual vertex label
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
      ii v = AdjList[u][j];                           // for each neighbors of u
      if (!dist.count(v.first)) {    // dist.find(v.first) == dist.end() also ok
        dist[v.first] = dist[u] + 1;                  // v unvisited + reachable
        p[v.first] = u;          // addition: the parent of vertex v->first is u
        q.push(v.first);                              // enqueue v for next step
      }
      else if ((dist[v.first] % 2) == (dist[u] % 2))              // same parity
        isBipartite = false;
  } }

  printf("\nShortest path: ");
  printPath(mapper[30]), printf("\n");
  printf("isBipartite? %d\n", isBipartite);

  return 0;
}
