/* 200 - Rare Order
Problem description:
- Topological Sort (on a Directed Acyclic Graph)

Mistakes made:
- Used a map to make the node pairs, although nodes in a graph can have multiple outgoing edges.
  Use multi-map instead.
- Competitive Programming suggests to use a modified DFS algorithm (pg 66 - vol.1)
*/

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef multimap<char, char>	mmcc;
typedef set<char>	sc;

#define TRmmcc(c, it)	for(mmcc::iterator it=(c).begin(); it!=(c).end(); ++it)
#define TRsc(c, it)		for(sc::iterator it=(c).begin(); it!=(c).end(); ++it)

int main()
{
	string line;
	vector<char> row;
	vector< vector<char> > list;

	// Build the list of strings.
	for (int i = 0; cin >> line; ++i)
	{
		if (line[0] == '#') break;
		
		list.push_back(row);

		for (int j = 0; j < line.size(); ++j)
		{
			list.at(i).push_back(line[j]);
		}
	}

	// Create the topological network.
	multimap<char, char> network;

	for (int row = 0; row < list.size()-1; ++row)
	{
		for (int col = 0; col < list.at(row).size(); ++col)
		{
			if (row+1 <= list.size())  // Make sure we're not out of bounds.
			{
				char u = list.at(row).at(col);
				char v = list.at(row+1).at(col);

				if (u != v)
				{
					// Found a collating sequence. Add to the map, then go to next line.
					network.insert( pair<char, char>(u, v) );
					break;
				}
				// Else, characters are the same; check the next character on the line.
			}
		}
	}

	set<char> s;  // Set of all nodes with no incoming edges.
  
  // Create a set of all nodes (remember, set means no duplicates).
	TRmmcc(network, it) 
	{
		s.insert(it->first);
		s.insert(it->second);
	}

	// Remove nodes that have incoming edges from the set.
	TRmmcc(network, it)
	{
		s.erase(it->second);
	}

  vector<char> l;  // This list will contain the sorted output.
  mmcc network2(network);  // We'll iterate through a copy because the original will be modified.

	// Perform a topological sort on the directed acyclic graph.
  while (!s.empty())
  {
    sc::iterator it = s.begin();  // Select a node n from S.
    l.push_back(*it);  // Insert n into L.
    s.erase(it);  // Remove n from S.

    // Find nodes with incoming edge from n.
    pair<mmcc::iterator, mmcc::iterator> ret = network2.equal_range(*it);  // equal_range() finds all pairs with a matching key.

    // For each m, remove edge and possibly place into set.
    for (mmcc::iterator i = ret.first; i != ret.second; ++i)
    {
      char n = i->first;
      char m = i->second;
      
      // Remove edge (i.e. remove pair).
      network.erase(network.find(n));
      
      // Does m have other incoming edges?
      bool edge_to_m = false;
      TRmmcc(network, iter)
      {
        // Iterate through the multimap and find pairs with m as value.
        if (iter->second == m)
        {
          edge_to_m = true;
          break;
        }
      }

      // Insert m into S if m has no other incoming edges.
      if (!edge_to_m)
        s.insert(m);
    }
  }

  // Print L.
  for (vector<char>::iterator it = l.begin(); it != l.end(); ++it)
    cout << *it;
  cout << endl;

	return 0;
}
