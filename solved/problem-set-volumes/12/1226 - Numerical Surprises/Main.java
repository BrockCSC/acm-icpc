/**
 * 1226 - Numerical Surprises
 * Simple modulus that requires BigInt
 * @author Dennis Ideler
 * javac Main.java && java Main < 1226.dat
 */

import java.util.Scanner;
import java.math.BigInteger;

class Main
{
  public static void main(String[] args)
  {
    Scanner in = new Scanner(System.in);

    int cases = in.nextInt();    // read # of test cases
    
    for (int i = 0; i < cases; ++i)
    {
//      String n_str = in.next(); // read n
//      String p_str = in.next(); // read p
//      BigInteger n = new BigInteger(n_str); // convert to bigint
//      BigInteger p = new BigInteger(p_str); // convert to bigint
      BigInteger n = new BigInteger.valueOf(in.nextInt()); // read and convert n
      BigInteger p = new BigInteger.valueOf(in.nextInt()); // read and convert p

      System.out.println(p.mod(n));
    }
  }
}
