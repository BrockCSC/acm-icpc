/* 1219 - Team Arrangement */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Player
{
  int number;
  string name;
  char role;
  int years;

  void toString()
  {
    cout << number << " " << name << " " << role << endl;
  }
};

// comparison function for sort
bool compare_players(Player a, Player b)
{
  return a.number < b.number;
}

// comparison function for max_element
bool compare_coaches(Player a, Player b)
{
  return a.years < b.years;
}

int main()
{
  string line;
  while (1) // for each test case
  {
    vector< vector<Player> > players;
    vector<Player> goalkeepers;
    vector<Player> defenders;
    vector<Player> middlefielders;
    vector<Player> strikers;

    players.push_back(goalkeepers);
    players.push_back(defenders);
    players.push_back(middlefielders);
    players.push_back(strikers);

    bool stop = false;
    // read in 22 lines
    // format: number name role year1-year1' year2-year2' ...
    // e.g. 9 PlayerA M 2000-2001 2003-2006  (note: years are inclusive, so 2001-2002 is 2 years)
    for (int i = 0; i < 22; ++i)
    {
      Player p;

      cin >> p.number;
      if (p.number == 0)
      {
        stop = true;
        break;
      }
      cin >> p.name; 
      cin >> p.role;

      // read the remainder of the line
      char raw_years[256];
      cin.getline(raw_years, 256, '\n');

      string years(raw_years); // need the power of the string class!

      // parse the years and calculate total years of play
      int num_pairs = years.size() / 10;
      int tot_years = 0;
      for (int pair = 0, j = 1; pair < num_pairs; ++pair, j+=10)
      {
        int year_s = atoi(years.substr(j, 4).c_str());
        int year_e = atoi(years.substr(j+5, 4).c_str());
        tot_years += (year_e - year_s) + 1; // +1 since ending year is inclusive
      }

      p.years = tot_years;

      // player record complete, insert into correct vector
      switch (p.role)
      {
        case 'G':
          goalkeepers.push_back(p);
//          cout << "inserted " << p.name << " in G" << endl;
          break;
        case 'D':
          defenders.push_back(p);
//          cout << "inserted " << p.name << " in D" << endl;
          break;
        case 'M':
          middlefielders.push_back(p);
//          cout << "inserted " << p.name << " in M" << endl;
          break;
        case 'S':
          strikers.push_back(p);
//          cout << "inserted " << p.name << " in S" << endl;
          break;
      }
    } // end of player records

    if (stop) // end of test cases
      break;

    // read and parse team formation
    string formation;
    cin >> formation;
    int d = formation[0] - '0'; // convert char to int
    int m = formation[2] - '0';
    int s = formation[4] - '0';
    
//    cout << d << " defenders, " << m << " middlefielders, " << s << " strikers" << endl;

    // sort each role vector based on player number
    sort(goalkeepers.begin(), goalkeepers.end(), compare_players);
    sort(defenders.begin(), defenders.end(), compare_players);
    sort(middlefielders.begin(), middlefielders.end(), compare_players);
    sort(strikers.begin(), strikers.end(), compare_players);

    // check if arrangement is possible
    if (goalkeepers.size() < 1 || defenders.size() < d || middlefielders.size() < m || strikers.size() < s)
    {
      cout << "IMPOSSIBLE TO ARRANGE\n" << endl;
      continue;
    }

    // create team vector and insert active players from each role
    vector<Player> team;
    
    team.push_back(goalkeepers.at(0));
    
    for (int i = 0; i < d; ++i)
      team.push_back(defenders.at(i));

    for (int i = 0; i < m; ++i)
      team.push_back(middlefielders.at(i));

    for (int i = 0; i < s; ++i)
      team.push_back(strikers.at(i));

    // calculate who is captain (longest record out of active players)
//    Player coach = *max_element(team, team+10, compare_coaches); // team size is 10 -- not working, try iteratively
    Player coach;
    coach.years = 0;
    coach.number = 0;
    for (int i = 0; i < team.size(); ++i)
    {
      if ((team[i].years > coach.years) || (team[i].years == coach.years && team[i].number > coach.number))
      {
        coach.years = team[i].years;
        coach.number = team[i].number;
        coach.name = team[i].name;
        coach.role = team[i].role;
      }
    }

    // remove captain from team vector
    for (int i = 0; i < team.size(); ++i)
    {
      if (team[i].number == coach.number)
      {
        team.erase(team.begin() + i);
        break;
      }
    }

    // print captain
    coach.toString();
  
    // print goalkeeper, defenders, middlefielders, strikers
    for (int i = 0; i < team.size(); ++i)
      team.at(i).toString();

    cout << endl;
  }

  return 0;
}
