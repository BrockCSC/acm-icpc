// Basic input & output with the Scanner class.
// You may also use the BufferedReader class, but it's more complicated.

import java.util.Scanner;

public class Main // Source file must contain a class named 'Main'
{
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in); // Read from System.in

    while (in.hasNext())
    {
      int i = in.nextInt();
      double d = in.nextDouble();
      String s = in.next();
      char c = s.charAt(2); // There is no nextChar(). Use next() and charAt().
      String line = in.nextLine(); // Read whole line (or rest of the line past '\n')

      // Use print(), println(), or printf() for output.
      System.out.println(i + " " + d + " " + s " " + " " + c + " " + line);
      System.out.printf("%4d, %6.2f, %s, %c\n", i, d, s, c); // Don't forget '\n'
    }
   }
}
