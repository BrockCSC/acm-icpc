/* 1203 - Argus */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Query
{
  int qnum;
  int period;
};

// comparison function for sort
bool compare_queries(Query a, Query b)
{
  if (a.period == b.period)
    return a.qnum < b.qnum;
  else
    return a.period < b.period;
}

int main()
{
  vector<Query> queries;
  
  string command;

  // read in register commands (stop when # encountered)
  while (cin >> command)
  {
    if (command[0] == '#')
      break;

    // else it's a register command
    Query q;
    cin >> q.qnum;
    cin >> q.period;

    queries.push_back(q);
  }

  // read in k
  int k;
  cin >> k;

  // calculate the return times of first k queries...

  // place each query (with their updated frequences) k times into the same vector
  vector<Query> sorted_queries;

  for (int i = 0; i < queries.size(); ++i)
  {
    int frequency = queries[i].period;
    int qnum = queries[i].qnum;

    for (int j = 0; j < k; ++j)
    {
      Query q;
      q.qnum = qnum;
      q.period = frequency + (j * frequency);

      sorted_queries.push_back(q);
    }
  }

  // then sort that vector
  sort(sorted_queries.begin(), sorted_queries.end(), compare_queries);

  // print first k queries
  for (int i = 0; i < k; ++i)
    cout << sorted_queries.at(i).qnum << endl;

  return 0;
}
