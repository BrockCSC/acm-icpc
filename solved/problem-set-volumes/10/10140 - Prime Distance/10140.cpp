#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <utility>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll _sieve_size;
bitset<10000010> bs;
vi primes;
vi _primes;

void sieve(ll upperbound)
{
  _sieve_size = upperbound + 1;
  bs.set();  // set all bits to 1 (assume all numbers are prime at first)
  bs[0] = bs[1] = 0;
  for (ll i = 2; i <= _sieve_size; ++i)
  {
    // cross out multiples of i, starting from i * i
    for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
    primes.push_back(static_cast<int>(i)); // push back every i?
  }
}

bool is_prime(ll N)
{
  if (N <= _sieve_size) return bs[N]; // O(1) for small primes
  for (int i = 0; i < static_cast<int>(primes.size()); ++i)
    if (N % primes[i] == 0) return false;
  return true;
}

int main(int argc, char** argv)
{
  cin.sync_with_stdio(false);
  sieve(1000000);
  //sieve(10000000);
  int L, U;
  while (cin >> L >> U)
  {
    //cout << L << " " << U << endl;
    int min_dist = 1000000;
    int max_dist = -1;
    pair<int, int> closest;
    pair<int, int> furthest;

    for (int i = L; i <= U; ++i) // find all primes within range
    {
      if (is_prime(i))
      {
        _primes.push_back(i);
      }
    }
    if (_primes.size() < 2)
    {
      cout << "There are no adjacent primes.\n";
    }
    else
    {
      for (int i = 0; i < _primes.size()-1; ++i) // iterate through all primes
      {
        int dist = _primes.at(i+1) - _primes.at(i);
        //cout << "dist " << _primes[i] << " to " << _primes[i+1] << " = " << dist << endl;
        if (dist < min_dist)
        {
          closest.first = _primes[i];
          closest.second = _primes[i+1];
          min_dist = dist;
        }
        if (dist > max_dist)
        {
          furthest.first = _primes[i];
          furthest.second = _primes[i+1];
          max_dist = dist;
        }
        //cout << _primes[i] << " ";
      }
      cout << closest.first << "," << closest.second << " are closest, "
           << furthest.first << "," << furthest.second << " are most distant.\n";
    }
    _primes.clear();
  }
  return 0;
} 
