#include <iostream>
#include <string>
#include <cstring> // for memset
#include <vector>
using namespace std;

// Note: cost of a cut is relative to the (sub)string that is being cut.
main()
{
  int alphabet[26];
  int ds; // datasets
  cin >> ds;
  for (int i = 0; i < ds; ++i)
  {
    int numcuts; // 1 <= # cuts <= 1000
    cin >> numcuts;
    int cutpos[numcuts];
    for (int j = 0; j < numcuts; ++j)
    {
      cin >> cutpos[j];
    }
    string s;
    cin >> s;
    vector<string> v1, v2;
    v1.push_back(s);
    int cost = 0;
    for (int j = 0; j < numcuts; ++j) // perform k cuts
    {
      memset(alphabet, 0, sizeof alphabet);
      int prev_size = 0, size = 0;
      bool cut = false;
      for (int k = 0; k < v1.size(); ++k) // find substring to cut
      {
        //TODO: if WA, ignore duplicate cut positions by storing cutpos in a set.
        prev_size = size;
        size += v1[k].size();
        if (cutpos[j] < size && !cut) // cut this substring
        {
          int cutindx = cutpos[j] - prev_size; // cut index relative to substring
          string substr1 = v1[k].substr(0, cutindx); // left side of cut
          string substr2 = v1[k].substr(cutindx); // right side of cut
          v2.push_back(substr1);
          v2.push_back(substr2);
          cut = true;

          // Calculate cost of the cut
          for (int l = 0; l < substr1.size(); ++l) // find unique chars in substr1
          {
            int idx = substr1[l] - 'a';
            if (!alphabet[idx]) // if first encounter of character
            {
              alphabet[idx] = 1;
              if (substr2.find(substr1[l]) == string::npos) cost++;
            }
          }
          for (int l = 0; l < substr2.size(); ++l) // find unique chars in substr2
          {
            int idx = substr2[l] - 'a';
            if (!alphabet[idx])
            {
              alphabet[idx] = 1;
              if (substr1.find(substr2[l]) == string::npos) cost++;
            }
          }
        }
        else // also push back any uncut substrings
        {
          v2.push_back(v1[k]);
        }
      }
      
      v1 = v2; // v1 drops its current elements and copies the contents of v2
      v2.clear(); // or `v2 = vector<string>();`

      //for (int t = 0; t < v1.size(); ++t)
      //  cout << v1.at(t) << " ";
      //cout << endl;
      //cout << "total cost = " << cost << endl;
    }
    cout << cost << endl;
  }
}
