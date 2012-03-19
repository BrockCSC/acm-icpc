/* C++: Maps template
   =================================================================
   Description: Template for STL maps/multimaps
   
   Complexity:  O(lg n) access
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Mar 19, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 
   Notes:       
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

int main(){
  // 1. Declaring a map: 
    // "map<key_type, value_type> m;" 
    map<int, int> int_intmap;
    map<string, int> string_intmap;
    map<int, string> int_stringmap;

    // With a different comparison operator:
    // "map<key_type, value_type, cmp> m;"
    map<int, int, greater<int> > dec_intmap;

  // 2. Assigning a value into the map
    //  "m[key_value] = value;"

    int_intmap[5] = 25;
    string_intmap["nine"] = 9;
    int_stringmap[9] = "nine";
    
  // 3. Checking if a value is in a map;
  //    "if(m.count(key) >= 0)"
    printf("%d\n", int_intmap.count(5));      // prints "1"
    printf("%d\n", int_intmap.count(4));      // prints "0"
    
  // 4. Accessing a value of the map
    //    x = m[key_value];
    printf("%d\n", int_intmap[5]);            // prints "25"
    printf("%d\n", string_intmap["nine"]);    // prints "nine"
    printf("%s\n", int_stringmap[9].c_str()); // prints "9"

    // ** The default value of something not in the map is 0.
    // ** HOWEVER accessing this element, adds it to the map
    printf("%d\n", int_intmap[4]);            // prints "0"
    printf("%d\n", int_intmap.count(4));      // NOW prints "1"
  
  // 5. Size of a map (# of keys)
    //  "m.size();";
    printf("%d\n", int_intmap.size());        // prints "2"

  // 6. Iterating through the map
    //  Map iterator returns a pair p
    //  p->first = the key value
    //  p->second = the map value for that key.
    //  Iteration is done in sorted key order (by default <less>)

    //  Declare an iterator
    //  map<key_type, value_type>::iterator it;
    map<int, int>::iterator it;
    for(it = int_intmap.begin(); it != int_intmap.end(); it++){
      printf("%d -> %d\n", it->first, it->second);
    }
    // prints "4 -> 0" then prints "5 -> 25"
    
  // 6. Removing an element from the map 
    //  "m.erase(key);" (key does not need to be in map)
    int_intmap.erase(5);
    printf("%d\n", int_intmap.size());        // prints "1"

  // 7. Clearing a map
    //  "m.clear();";
    int_intmap.clear();
    printf("%d\n", int_intmap.size());        // prints "0"

  return 0;
}
