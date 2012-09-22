import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;


public class Main {
	public Main () {
		
	}


	public void work (){
		Scanner scan = new Scanner(System.in);

		int numCases = scan.nextInt();
		BigInteger P;
		BigInteger N;

		for (int i = numCases; i > 0 ;i--) {
			N = scan.nextBigInteger();
			P = scan.nextBigInteger();

			System.out.println(P.mod(N));
		}

		scan.close();

	}

	public static void main(String[] args) { new Main().work(); }
}
