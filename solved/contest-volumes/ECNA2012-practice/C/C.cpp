#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct Actor
{
  string name;
  int height;
};

bool compare_actors(Actor a, Actor b)
{
  return a.height > b.height;
}

main()
{
  int n;
  int num_case = 1;
  while (cin >> n)
  {
    if (n == 0) break;
    cout << "Case " << num_case++ << ":" << endl;
    vector<Actor> actors;
    for (int i = 0; i < n; ++i)
    {
      Actor a;
      cin >> a.name >> a.height;
      actors.push_back(a);
    }
    sort(actors.begin(), actors.end(), compare_actors);
    vector<Actor> cast;
    // for each actor, check the remaining actors for possible cast
    for (int i = 0; i < actors.size(); ++i)
    {
      bool son_found = false, grandson_found = false;
      int son_h = actors[i].height - 3;
      int grandson_h = actors[i].height - 9;
      for (int j = i+1; j < actors.size(); ++j)
      {
        if (!son_found && actors[j].height == son_h)
        {
          son_found = true;
          cast.push_back(actors[i]);
          cast.push_back(actors[j]);
        }
        if (son_found && !grandson_found && actors[j].height == grandson_h)
        {
          grandson_found = true;
          cast.push_back(actors[j]);
          break;
        }
      }
      if (son_found && grandson_found)
      {
        for (int idx = 0; idx < 3; ++idx)
          cout << cast[idx].name << " ";
        cout << endl;
      }
      cast.clear();
      son_found = false; grandson_found = false;
    }
  }
}
