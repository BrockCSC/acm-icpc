#include <iostream>
#include <vector>
using namespace std;

main()
{
  int k;
  cin >> k;
  while (true)
  {
    vector<int> S;
    for (int i = 0; i < k; ++i)
    {
      int s;
      cin >> s;
      S.push_back(s);
    }
    // Note that the complete search has been pruned.
    for (int i = 0; i < S.size()-5; ++i) // 1
    {
      for (int j = 1; j < S.size()-4; ++j) // 2
      {
        if (j <= i) continue;  // These conditions guarantee the ascending order.
        for (int k = 2; k < S.size()-3; ++k) // 3
        {
          if (k <= j) continue;
          for (int l = 3; l < S.size()-2; ++l) // 4
          {
            if (l <= k) continue;
            for (int m = 4; m < S.size()-1; ++m) // 5
            {
              if (m <= l) continue;
              for (int n = 5; n < S.size(); ++n) // 6
              {
                if (n <= m) continue;
                cout << S[i] << " " << S[j] << " " << S[k] << " " << S[l] << " "
                     << S[m] << " " << S[n] << "\n";
              }
            }
          }
        }
      }
    }
    cin >> k;  // Read k at the end so we can break before printing a newline.
    if (k == 0) break;
    cout << endl;
  }
}
