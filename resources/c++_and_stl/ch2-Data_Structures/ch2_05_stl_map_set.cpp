#include <cstdio>
#include <map>
#include <set>
#include <string>
using namespace std;

int main() {
  char name[20];
  int value;
  // note: there are many clever usages of this set/map
  // that you can learn by looking at top coder's codes
  // note, we don't have to use .clear() if we have just initialized the set/map
  set<int> used_values; // used_values.clear();
  map<string, int> mapper; // mapper.clear();

  // suppose we enter these 7 name-score pairs via keyboard
  /*
  john 78
  billy 69
  andy 80
  steven 77
  felix 82
  grace 75
  martin 81
  */
  for (int i = 0; i < 7; i++) {
    scanf("%s %d", &name, &value);
    mapper[name] = value;                                         // map example
    used_values.insert(value);                                    // set example
  }

  // then the internal content of mapper MAY be something like this:
  // re-read balanced BST concept if you do not understand this diagram
  // the keys are names (string)!
  //                        (grace,75) 
  //           (billy,69)               (martin,81)   
  //     (andy,80)   (felix,82)    (john,78)  (steven,77)

  // iterating through the content of mapper will give a sorted output
  // based on keys (names)
  for (map<string, int>::iterator it = mapper.begin(); it != mapper.end(); it++)
    printf("%s %d\n", ((string)it->first).c_str(), it->second);

  // map can also be used like this
  printf("steven's score is %d, grace's score is %d\n",
    mapper["steven"], mapper["grace"]);
  printf("==================\n");

  // the internal content of used_values MAY be something like this
  // the keys are values (integers)!
  //                 (78) 
  //         (75)            (81)   
  //     (69)    (77)    (80)    (82)

  // O(log n) search, found
  printf("%d\n", *used_values.find(77));
  // O(log n) search, not found
  if (used_values.find(79) == used_values.end())
    printf("79 not found\n");

  return 0;
}
