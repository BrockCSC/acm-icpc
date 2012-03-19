#include <iostream>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

int get_sighting(char bird, string sightings, int interval)
{
  if (bird == sightings[0] || sightings.size() == 0)
    return interval;
  
  return get_sighting(bird, sightings.substr(1,sightings.size()), interval+1);
}

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
    // recursively check for sightings
    FOR(j,0,line.size()) // for each sighting
    {
      char bird = line[j];
      if (bird == '.') continue;
      int interval = get_sighting(bird, line.substr(j,line.size(), 0));
      cout << interval << endl;
      /*
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
      */
    }
    cout << winning_birds << ": " << longest_interval << endl;
  }
  return 0;
}
