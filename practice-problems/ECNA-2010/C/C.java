/* solution to 3D Maze */
import java.util.*;
class Node {
  public char dir;
  public Node parent;
  public int x,y,z;
  public Node(char d,Node p, int x, int y, int z) {
    dir = d; this.parent = p; this.x = x; this.y = y; this.z = z;
  }
}

public class Maze {
  public static Scanner in;
  public static int n;
  public static int caseNum;
  public static final int F = 0, R = 1, B = 2, L = 3, U = 4, D = 5;
  public static char[][][] maze;
  public static int x,y,z; // location of the center of the rod structure
  public static boolean solved;
  public static LinkedList<Node> q;

  //      4
  //      U
  // 3 L  |  B 2
  //    \ | /
  //     \|/
  //     /|\
  //    / | \
  //  F   |  R
  //  0   D  1
  //      5


  //   U       U       U       U       B       F
  // L F R   F R B   R B L   B L F   L U R   L D R
  //   D       D       D       D       F       B
  //   
  //   0       1       2       3       4       5
  
  public static void main(String[] args) {
    in = new Scanner(System.in);
    caseNum = 0;
    while (true) {
      n = in.nextInt();
      if (n == 0) break;
      caseNum++;
      in.nextLine(); // skip past \n after value of n
      maze = new char[6][n][n];
      for (int i = 0; i < 6; i++) {
	for (int j = 0; j < n; j++) {
          String line = in.nextLine();
	  for (int k = 0; k < n; k++)
	    maze[i][j][k] = line.charAt(k); 
	}
      }

//      print();

      // "flip" some faces so directions align:
      // Four faces get flipped left to right:
      flipLR(F);
      flipLR(L);
      flipLR(U);
      flipLR(D);
      // Five faces get flipped top to bottom:
      flipTB(F);
      flipTB(R);
      flipTB(L);
      flipTB(B);
      flipTB(U);
      x=1; y=1; z=1;
      maze[F][1][1] = maze[B][1][1] = maze[L][1][1] = maze[R][1][1]
           = maze[U][1][1] = maze[D][1][1] = '.';
      
      solved = false;

      solve();
      if (!solved)
        System.out.println("No solution");
    }   
  }

  // For debugging use only:
  public static void print() {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
	  System.out.print(maze[i][j][k]);
	}
	System.out.println();
      }
      System.out.println();
    }
  }

  public static void solve() {
    q = new LinkedList<Node>();
    HashSet<Integer> visited;
    // initialize the queue with initial position:
    Node nod = new Node(' ',null,1,1,1);
    q.addLast(nod);
    visited = new HashSet<Integer>();
    while (q.size() > 0) {
      Node nd = q.removeFirst();
      x = nd.x; y = nd.y; z = nd.z;

  
      x = nd.x; y = nd.y; z = nd.z;
      if (visited.contains(x+100*y+10000*z)) continue;
      visited.add(x+100*y+10000*z);
      
      if (x == n-2 && y == n-2 && z == n-2) {
        solved = true;
        printSol(nd);
        System.out.println();
        return;
      }
      
      // Try all possible next moves, 
      for (int i = 0; i < "FBLRUD".length(); i++) {
        String temp = "";
        switch ("FBLRUD".charAt(i)){
          // F,B: x axis; row,col = z,y
          //  "F,B": maze[L,R][z][x] --> maze[L,R][z][x-+1]
          //         maze[U,D][x][y] --> maze[U,D][x-+1][y]
  
          case 'F': if (x <= 1) break;

                    temp = ""+maze[L][z][x-1] + maze[R][z][x-1] 
                        + maze[U][x-1][y] + maze[D][x-1][y];
                    if (temp.indexOf("X") < 0 && 
                        !visited.contains(x-1+y*100+z*10000)) {
                        Node tmp = new Node('F',nd,x-1,y,z);
                          q.addLast(tmp);
                      }
                      break;
  
          case 'B': if (x >= n-2) break;
                    temp = ""+maze[L][z][x+1] + maze[R][z][x+1] +
                         maze[U][x+1][y] + maze[D][x+1][y];
                    if (temp.indexOf("X") < 0 && 
                        !visited.contains(x+1+y*100+z*10000)) {
                        Node tmp = new Node('B',nd,x+1,y,z);
                          q.addLast(tmp);
                      }
  
                      break;
  
          //  L,R: y axis; row,col = z,x
          //  "L,R": maze[U,D][x][y] --> maze[U,D][x][y+-1]
          //         maze[F,B][z][y] --> maze[F,B][z][y+-1]
          case 'L': if (y >= n-2) break;
                    temp = ""+maze[U][x][y+1] + maze[D][x][y+1] +
                      maze[F][z][y+1] + maze[B][z][y+1];
                    if (temp.indexOf("X") < 0 &&
                        !visited.contains(x+(y+1)*100+z*10000)) {
                        Node tmp = new Node('L',nd,x,y+1,z);
                          q.addLast(tmp);
                      }
  
                      break;
          case 'R': if (y <= 1) break;
                    temp = ""+maze[U][x][y-1] + maze[D][x][y-1] +
                      maze[F][z][y-1] + maze[B][z][y-1];
                    if (temp.indexOf("X") < 0 &&
                        !visited.contains(x+(y-1)*100+z*10000)) {
                        Node tmp = new Node('R',nd,x,y-1,z);
                          q.addLast(tmp);
                      }
  
                      break;
          // U,D: z axis; row,col = x,y
          //  "U,D": maze[F,B][z][y] --> maze[F,B][z+-1][y]
          //         maze[L,R][z][x] --> maze[L,R][z+-1][x]
          case 'U': if (z >= n-2) break;
                    temp = ""+maze[F][z+1][y] + maze[B][z+1][y] +
                      maze[L][z+1][x] + maze[R][z+1][x];
                    if (temp.indexOf("X") < 0 &&
                        !visited.contains(x+y*100+(z+1)*10000)) {
                        Node tmp = new Node('U',nd,x,y,z+1);
                          q.addLast(tmp);
                      }
  
                      break;
          case 'D': if (z <= 1) break;
                    temp = ""+maze[F][z-1][y] + maze[B][z-1][y] +
                      maze[L][z-1][x] + maze[R][z-1][x];
                    if (temp.indexOf("X") < 0 &&
                        !visited.contains(x+y*100+(z-1)*10000)) {
                        Node tmp = new Node('D',nd,x,y,z-1);
                          q.addLast(tmp);
                      }
                      break;
        }
      }
    }
    return;
  }

  public static void flipLR(int side) {
      for (int i = 1; i < n; i++) {
        for (int j = 1; j < n/2; j++) {
          // Flip side left to right
          char temp = maze[side][i][j];
          maze[side][i][j] = maze[side][i][n-j-1];
          maze[side][i][n-j-1] = temp;
        }
      }
  }

  public static void flipTB(int side) {
      for (int i = 1; i < n; i++) {
        for (int j = 1; j < n/2; j++) {
          // Flip side top to bottom
          char temp = maze[side][j][i];
          maze[side][j][i] = maze[side][n-j-1][i];
          maze[side][n-j-1][i] = temp;
        }
      }
  }

  public static void printSol(Node nd)
  {
    if (nd.parent == null) return;
    printSol(nd.parent);
    System.out.print(nd.dir);
  }
}
