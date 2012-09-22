import java.io.*;
import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {

        public Main(){
            Scanner in = new Scanner(System.in);
            int times = in.nextInt();               
            	for(int i = 0; i < times; i++){
                  	BigInteger N = in.nextBigInteger();                                
                        BigInteger P = in.nextBigInteger();
				System.out.println(P.mod(N));
			}   
        }

      public static void main(String[] args){
                new Main();
        }
}

