import java.io.*;
import java.lang.*;
import java.util.*;
import java.math.*;


public class Main {
	public Main () {
		
	}

	public void work (){
		int N;
		int R;
		int tree[];

		Scanner scan = new Scanner(System.in);
		
		N = scan.nextInt();
		R = scan.nextInt();		

		tree = new int[N];
		for (int i = 0; i<N; i++) {
			tree[i] = scan.nextInt();
		}

		// read edges

		// start solving stuff


		scan.close();
	}

	public static void main(String[] args) { new Main().work(); }
}
