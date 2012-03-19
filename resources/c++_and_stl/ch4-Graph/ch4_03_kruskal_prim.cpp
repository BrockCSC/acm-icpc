#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

// Union-Find Disjoint Sets Library
// PS: This library code does not include the `union by rank' heuristic yet
// 1000 is just a rough number, adjustable by user
vi pset(1000), setSize(1000); int _numDisjointSets;
void initSet(int N) { setSize.assign(N, 1); _numDisjointSets = N; 
pset.assign(N, 0); for (int i = 0; i < N; i++) pset[i] = i; }
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { 
  if (!isSameSet(i, j)) { 
    _numDisjointSets--; 
    setSize[findSet(j)] += setSize[findSet(i)]; 
    pset[findSet(i)] = findSet(j); } }
int numDisjointSets() { return _numDisjointSets; }
int sizeOfSet(int i) { return setSize[findSet(i)]; }

vector<vii> AdjList;
vi taken;                                  // global boolean flag to avoid cycle
priority_queue<ii> pq;            // priority queue to help choose shorter edges

void process(int vtx) {
  taken[vtx] = 1;
  for (int j = 0; j < AdjList[vtx].size(); j++) {
    ii v = AdjList[vtx][j];
    if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
} }  // sort by (inc) weight then by (inc) id by using -ve sign to reverse order

int main() {
  int V, E, u, v, w;

  /*
  // Graph in Figure 4.9 left/4.10, format: list of weighted edges
  // This example shows another form of reading graph input
  5 7
  0 1 4
  0 2 4
  0 3 6
  0 4 6
  1 2 2
  2 3 8
  3 4 9
  */

  scanf("%d %d", &V, &E);

  // Kruskal's algorithm merged with Prim's algorithm
  AdjList.assign(V, vii());
  vector< pair<int, ii> > EdgeList;  // format: weight, two vertices of the edge
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &u, &v, &w);                 // read the triple: (a, b, w)
    EdgeList.push_back(make_pair(w, ii(u, v)));    // but store it as: (w, a, b)
    AdjList[u].push_back(ii(v, w));
    AdjList[v].push_back(ii(u, w));
  }
  sort(EdgeList.begin(), EdgeList.end());   // sort by edge weight in O(E log E)

  int mst_cost = 0; initSet(V);             // all V are disjoint sets initially
  for (int i = 0; i < E; i++) {                           // for each edge, O(E)
    pair<int, ii> front = EdgeList[i];
    if (!isSameSet(front.second.first, front.second.second)) {    // if no cycle
      mst_cost += front.first;                     // add the weight of e to MST
      unionSet(front.second.first, front.second.second);       // link endpoints
  } }                            // note: the runtime cost of UFDS is very light

  // note: the number of disjoint sets must eventually be one for a valid MST
  printf("MST cost = %d (Kruskal's)\n", mst_cost);



// inside int main() --- assume the graph has been stored in AdjList
  taken.assign(V, 0);
  process(0);        // take vertex 0 and process all edges incident to vertex 0
  mst_cost = 0;
  while (!pq.empty()) {     // repeat until V vertices (E = V-1 edges) are taken
    ii front = pq.top(); pq.pop();
    u = -front.second, w = -front.first;       // negate the id and weight again
    if (!taken[u])                        // we have not connect this vertex yet
      mst_cost += w, process(u);   // take u and process all edges incident to u
  }                                             // each edge is in pq only once!
  printf("MST cost = %d (Prim's)\n", mst_cost);

  // take a vertex of the graph to be added to MST
  // here, we take vertex 0 for simplicity
  //vi taken(V, 0); taken[0] = 1;    // boolean flag to avoid cycle; take vertex 0
  //priority_queue<ii> pq;
  //for (int j = 0; j < AdjList[0].size(); j++) {  // start with edges of vertex 0
  //  ii v = AdjList[0][j];
  //  pq.push(ii(-v.second, -v.first));   // sort by (inc) weight then by (inc) id
  //}                        // trick: use negative sign to reverse the sort order

  //mst_cost = 0;
  //while (!pq.empty()) {     // repeat until V vertices (E = V-1 edges) are taken
  //  ii front = pq.top(); pq.pop();
  //  u = -front.second, w = -front.first;       // negate the id and weight again
  //  if (!taken[u]) {                    // we have not connected this vertex yet
  //    taken[u] = 1; mst_cost += w; // flag this vertex as taken + add its weight
  //    for (int j = 0; j < AdjList[u].size(); j++) {
  //      ii v = AdjList[u][j];                   // each edge is in pq only once!
  //      if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
  //} } }
  //  
  //printf("MST cost = %d (Prim's)\n", mst_cost);

  return 0;
}
