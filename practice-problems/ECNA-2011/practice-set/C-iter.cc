#include <iostream>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

int main()
{
  int n;
  cin >> n;

  string line;
  FOR(i,0,n) // for each test case
  {
    cin >> line;
    int longest_interval = -1;
    string winning_birds = "";
    FOR(j,0,line.size()) // for each sighting
    {
      char bird = line[j];
      if (bird == '.') continue;
      FOR(k,j+1,line.size()) // search later sightings to calculate interval;
      {
        if (bird == line[k]) // if bird is sighted again, check interval
        {
          int interval = k - j;
          if (interval > longest_interval) // wipe previous winners, record new winner
          {
            winning_birds = bird;
            longest_interval = interval;
          }
          else if (interval == longest_interval) // add additional winning bird
          {
            winning_birds += bird;
          }
          break; // don't check any further
        }
      }
    }
    cout << winning_birds << ": " << longest_interval << endl;
  }
  return 0;
}
