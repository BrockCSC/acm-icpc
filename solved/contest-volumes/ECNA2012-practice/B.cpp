#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

main()
{
  unsigned n; // max 100,000
  unsigned tc = 0;
  vector<int> v;
  vector< vector< int > > partitions;
  while (cin >> n)
  {
    if (n == 0) break;
    int m = 0;
    for (int i = 1; i < (n/2)+1; ++i)
    {
      int sum = 0;
      v.clear();
      for (int j = i; sum < n; ++j)
      {
        sum += j;
        v.push_back(j);
        if (sum == n)
        {
          m++;
          partitions.push_back(v);
          break;
        }
      }
    }
    cout << "Case " << ++tc << ": " << m << endl;
    for (int i = 0; i < m; ++i)
      cout << partitions[i][0] << " " << partitions[i][partitions[i].size()-1] << endl;
    partitions.clear();
  }
}
