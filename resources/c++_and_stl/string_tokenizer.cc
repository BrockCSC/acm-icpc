/* C++ - String Tokenizer
   =================================================================
   Description: Takes a string and divides it into either substrings
                or ints
   Complexity:  O(M) - M the length of the string
   -----------------------------------------------------------------
   Author:      Scott Crosswhite
   Date:        Feb 10, 2003
   References: 
   -----------------------------------------------------------------
   Reliability: 0
   Notes:
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* Subdivide it into strings separated by the characters in div */
vector<string> makeStringTokens (string s, string div) {
  vector<string> items;
  int i=0, j;

  for (i=s.find_first_not_of(div, i); i!=-1; i=s.find_first_not_of(div, i=j)) {
    j = s.find_first_of(div, i);
    items.push_back(s.substr(i, j-i));
  }
  return items;
}

/* Subdivide it into ints separated by the characters in div */
vector<int> makeIntTokens (string s, string div) {
  vector<int> items;
  int i=0, j;

  for (i=s.find_first_not_of(div, i); i!=-1; i=s.find_first_not_of(div, i=j)) {
    j = s.find_first_of(div, i);
    items.push_back(atoi(s.substr(i, j-i).c_str()));
  }
  return items;
}


int main () {
  string testString = "This is a test", testInt = "4:5:6:7:8";
  unsigned int i;

  vector<string> resString = makeStringTokens(testString, " ");
  vector<int>resInt = makeIntTokens(testInt, ":");

  cout << "Result of tokenizing the string: \"" 
       << testString
       << "\"" << endl;

  for (i=0; i<resString.size(); i++) 
    cout << "  " << resString[i] << endl;

  cout << endl << "Result of tokenizing the string: \""
       << testInt << "\"" << endl;

  for (i=0; i<resInt.size(); i++) 
    cout << "  " << resInt[i] << endl;

  return 0;
}
