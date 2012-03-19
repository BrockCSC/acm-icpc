import java.util.*;

class ch2_05_TreeMap_TreeSet {
  public static void main(String[] args) {
    // note: there are many clever usages of this set/map
    // that you can learn by looking at top coder's codes
    TreeSet<Integer> used_values = new TreeSet<Integer>(); // must use TreeSet as Set is an abstract class
    used_values.clear();
    TreeMap<String, Integer> mapper = new TreeMap<String, Integer>(); // must use TreeMap as Map is an abstract class
    mapper.clear();

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
    Scanner sc = new Scanner(System.in); // for reading input
    for (int i = 0; i < 7; i++) { // just need to repeat 7 times
      String name = sc.next();
      int value = sc.nextInt();
      sc.nextLine(); // to clear this line for reading the next name
      mapper.put(name, value); // map example
      used_values.add(value); // set example
    }

    // then the internal content of mapper MAY be something like this:
    // re-read balanced BST concept if you do not understand this diagram
    // the keys are names (string)!
    //                        (grace,75) 
    //           (billy,69)               (martin,81)   
    //     (andy,80)   (felix,82)    (john,78)  (steven,77)

    // iterating through the content of mapper will give a sorted output
    // based on keys (names)
    System.out.println(mapper.keySet());
    System.out.println(mapper.values());

    // map can also be used like this
    System.out.println("steven's score is " + mapper.get("steven") + ", grace's score is " + mapper.get("grace"));
    System.out.println("==================");

    // the internal content of used_values MAY be something like this
    // the keys are values (integers)!
    //                 (78) 
    //         (75)            (81)   
    //     (69)    (77)    (80)    (82)

    // O(log n) search, found
    System.out.println(used_values.contains(77)); // returns true
    System.out.println(used_values.headSet(77)); // returns [69, 75] (these two are before 77 in the inorder traversal of this BST)
    System.out.println(used_values.tailSet(77)); // returns [77, 78, 80, 81, 82] (these five are equal or after 77 in the inorder traversal of this BST)
    // O(log n) search, not found
    if (!used_values.contains(79))
      System.out.println("79 not found");
  }
}
