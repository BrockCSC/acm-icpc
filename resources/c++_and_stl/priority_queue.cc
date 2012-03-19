/* C++: Priority Queue template
   =================================================================
   Description: Template for using C++ STL priority queues
                
                Given an adjacency matrix of a weighted graph, and
		a source vertex s, finds the shortest path from
		source to all other vertices and stores it in dist[]
   
   Complexity:  lg(N) access time, where N is size of queue
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 31, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       q.top()   returns the LARGEST element in the queue,
                          as defined by the < operator
			  -> if X < Y, then Y is first on the queue
		q.pop()   removes the largest element of the queue
		q.push(X) adds X onto the queue
		q.empty() returns 1 if queue is empty, 0 otherwise
*/

#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 300
int adj[MAXN][MAXN];
int dist[MAXN];

struct Node{
  int node, cost;

  // i.e Node o is higher up in priority in the queue
  bool operator<(Node const &o) const {
    return cost > o.cost;
  }
};

int main(){
  int n, i, j; Node start, curr, next;
  
  while(scanf("%d", &n) == 1){       // Read # of vertices 
    for(i = 0; i < n; i++)           // Read adjacency matrix 
      for(j = 0; j < n; j++) 
	scanf("%d", &adj[i][j]);
    scanf("%d", &start.node);        // Get source vertex
    start.cost = 0;
    memset(dist, -1, sizeof(dist));  // Initialize distance 

    priority_queue<Node> q;          // Initialize queue
    q.push(start);                   
    while(!q.empty()){
      curr = q.top();
      q.pop();
      if(dist[curr.node] == -1){
	dist[curr.node] = curr.cost;
	for(i = 0; i < n; i++){
	  if(dist[i] != -1 || adj[curr.node][i] == -1) continue;
	  next.node = i;
	  next.cost = curr.cost + adj[curr.node][i];
	  q.push(next);
	}
      }
    }
    for(i = 0; i < n; i++)
      printf("Distance from %d to %d: %d\n", start.node, i, dist[i]);
  }
  return 0;
}




