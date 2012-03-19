// JDK 1.5 Program Template for ICPC Online Judge

import java.util.Scanner;

public class Main {   // save as Main.java
   public static void main(String[] args)
   {
      Scanner in = new Scanner(System.in);

      int    i = in.nextInt();    // read int
      double d = in.nextDouble(); // read double
      String s = in.next();       // read String
      char c = s.charAt(2); // There is no nextChar(), use next() and charAt()
      String line = in.nextLine(); // Read whole line (or rest of the line past '\n')

      System.out.printf("%4d, %6.2f, %s, %c\n", i, d, s, c);
      // Use %f for double (not %lf)
      // Don't forget to print the '\n'
   }
}
