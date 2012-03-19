#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;

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

int main() {
  printf("Assume that there are 5 disjoint sets initially\n");
  initSet(5); // create 5 disjoint sets
  unionSet('A' - 'A', 'B' - 'A'); // unionSet(A, B)
  unionSet('A' - 'A', 'C' - 'A'); // unionSet(A, C)
  unionSet('D' - 'A', 'B' - 'A'); // unionSet(D, B)
  printf("findSet(A) = %d\n", findSet('A' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(B) = %d\n", findSet('B' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(C) = %d\n", findSet('C' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(D) = %d\n", findSet('D' - 'A')); // will return 2 (the parent ID of 'A', 'B', 'C', 'D')
  printf("findSet(E) = %d\n", findSet('E' - 'A')); // will return 4 (the parent ID of 'E')
  printf("isSameSet(A, E) = %d\n", isSameSet('A' - 'A', 'E' - 'A')); // will return 0 (false)
  printf("isSameSet(A, B) = %d\n", isSameSet('A' - 'A', 'B' - 'A')); // will return 1 (true)

  return 0;
}
