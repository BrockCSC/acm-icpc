// can read input file 2 ways:
// 1) cat input.dat | ./program
// 2) ./program < input.dat

#include <string>
#include <iostream>
using namespace std;

int main(void)
{

/* sample input/output for subtracting the higher number with the lower number and outputting the result */
/*
 long long a,b,c;

 while(cin >> a >> b)
 {
  if(b > a) c = b-a;
  else c = a-b;
  cout << c << endl;
 }
*/

/* prints out the input you feed it */
 string str;

 while(cin >> str)
 {
  cout << str << endl;
 }

 return 0;
}
