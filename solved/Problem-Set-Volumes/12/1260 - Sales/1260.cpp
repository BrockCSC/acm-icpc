#include <iostream>
#include <vector>
using namespace std;
main()
{
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) // for each test case
  {
    int n;
    cin >> n;
    vector<int> A;
    vector<int> B;
    for (int i = 0; i < n; ++i) // for each daily sale
    {
      int sale;
      cin >> sale;
      A.push_back(sale);
    }
    // calculate B list
    int b = 0;
    if (A.size() > 1) for (int i = 1; i < A.size(); ++i)
    {
      for (int j = 0; j < i; ++j)
      {
        if (A[j] <= A[i]) b++;
      }
    }
    cout << b << endl;
  }
}
